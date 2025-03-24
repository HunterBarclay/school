#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>
#include <readline/history.h>

#include "Command.h"
#include "error.h"
#include "Utils.h"

/* Command internal representation. */
typedef struct {
  char *file;
  char **argv;
  char *in_file;
  char *out_file;
  int is_out_pipe;
  int pid;
} * CommandRep;

/* Provided definitions for creating built in functions */

#define BIARGS CommandRep r, int *eof, Jobs jobs
#define BINAME(name) bi_##name
#define BIDEFN(name) static void BINAME(name)(BIARGS)
#define BIENTRY(name)     \
  { #name, BINAME(name) }

/* State variables for builtin commands */
static char *owd = 0;
static char *cwd = 0;

/**
 * Determine if command has the correct number of arguments.
 */
static void builtin_args(CommandRep r, int n) {
  char **argv = r->argv;
  for (n++; *argv++; n--)
    ;
  if (n)
    ERROR("wrong number of arguments to builtin command"); // warn
}

/**
 * Exit command. Will signal the shell to wait for commands and close.
 */
BIDEFN(exit) {
  builtin_args(r, 0);
  *eof = 1;
}

/**
 * Present working directory command. Get current working directory.
 */
BIDEFN(pwd) {
  builtin_args(r, 0);
  if (!cwd)
    cwd = getcwd(0, 0);
  printf("%s\n", cwd);
}

/**
 * Change directory command. Changes the current working directory.
 */
BIDEFN(cd) {
  builtin_args(r, 1);
  if (!cwd)
    cwd = getcwd(0, 0);

  char *nextPath = r->argv[1];
  if (strcmp(r->argv[1], "-") == 0) {
    char *twd = cwd;
    nextPath = owd;
    owd = twd;
  } else {
    if (owd)
      free(owd);
    owd = cwd;
  }
  if (chdir(nextPath))
    ERROR("chdir() failed"); // warn
  
  cwd = getcwd(0, 0);
  if (!cwd)
    ERROR("Failed to get current working directory.");
}

/**
 * History command. Get list of commands used.
 */
BIDEFN(history) {
  builtin_args(r, 0);
  HIST_ENTRY **hist = history_list();
  if (!hist)
    return;
  HISTORY_STATE *state = history_get_history_state();
  if (!state || state->length == 0)
    return;
  int i = 0;
  HIST_ENTRY *entry = hist[0];
  char *printFormat = NULL;
  asprintf(&printFormat, "[%%%dd] %%s\n", (int)floor(log10((double)state->length)) + 1);
  while (entry) {
    printf(printFormat, i + 1, entry->line);
    ++i;
    entry = hist[i];
  }
}

/**
 * Try to execute builtin command.
 */
static int builtin(BIARGS) {
  typedef struct {
    char *s;
    void (*f)(BIARGS);
  } Builtin;
  static const Builtin builtins[] = {
      BIENTRY(exit), BIENTRY(pwd), BIENTRY(cd), BIENTRY(history), {0, 0}};
  int i;
  for (i = 0; builtins[i].s; i++)
    if (!strcmp(r->file, builtins[i].s)) {
      builtins[i].f(r, eof, jobs);
      return 1;
    }
  return 0;
}

/**
 * Build argument list from interpreted words.
 */
static char **getargs(T_words words) {
  int n = 0;
  T_words p = words;
  while (p) {
    p = p->words;
    n++;
  }
  char **argv = (char **)malloc(sizeof(char *) * (n + 1));
  if (!argv)
    ERROR("malloc() failed");
  p = words;
  int i = 0;
  while (p) {
    argv[i++] = strdup(p->word->s);
    p = p->words;
  }
  argv[i] = 0;
  return argv;
}

extern Command newCommand(T_command command) {
  if (!command->words)
    ERROR("No words in command");

  CommandRep r = (CommandRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");

  r->argv = getargs(command->words);
  r->file = r->argv[0];
  if (command->redir->in_word)
    r->in_file = strdup(command->redir->in_word->s);
  else
    r->in_file = NULL;
  if (command->redir->out_word)
    r->out_file = strdup(command->redir->out_word->s);
  else
    r->out_file = NULL;

  r->is_out_pipe = 0;
  r->pid = 0;
  return r;
}

/**
 * Run command. Will spawn child process for non builtin or background commands.
 */
static void child(CommandRep r, int fg) {
  int eof = 0;
  Jobs jobs = newJobs();

  if (!r->in_file && !fg) {
    r->in_file = strdup("/dev/null");
  }

  if (r->in_file) {
    int in_fd = open(r->in_file, O_RDONLY);
    if (in_fd == -1) {
      ERROR("Failed to open input file.");
    }
    if (dup2(in_fd, STDIN_FILENO) == -1) {
      ERROR("Failed to redirect standard input.");
    }
  }

  if (r->out_file) {
    int out_fd = -1;
    if (r->is_out_pipe) {
      out_fd = open(r->out_file, O_WRONLY);
    } else {
      out_fd = open(r->out_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    }
    if (out_fd == -1) {
      ERROR("Failed to open output file.");
    }
    if (dup2(out_fd, STDOUT_FILENO) == -1) {
      ERROR("Failed to redirect standard output.");
    }
  }

  if (builtin(r, &eof, jobs))
    exit(0);
  execvp(r->argv[0], r->argv);
  ERROR("execvp() failed");
  exit(0);
}

extern void execCommand(Command command, Pipeline pipeline, Jobs jobs,
                        int *jobbed, int *eof, int fg) {
  CommandRep r = command;
  if (fg && builtin(r, eof, jobs))
    return;
  if (!*jobbed) {
    *jobbed = 1;
    addJobs(jobs, pipeline);
  }

  int pid = fork();
  if (pid == -1)
    ERROR("fork() failed");
  if (pid == 0)
    child(r, fg); // Will not return

  r->pid = pid;
}

extern void pipeCommand(Command prev, Command next) {
  CommandRep r_prev = prev;
  CommandRep r_next = next;

  if (!r_prev->out_file && !r_next->in_file) {
    // If neither commands have out/in files specified, make them a new pipe.
    char *fifo;
    asprintf(&fifo, "/tmp/viekcodd8395-%d", rand());
    if (mkfifo(fifo, S_IRWXU) == -1) {
      if (errno != EEXIST) {
        ERROR("Failed to create pipeline.");
      }
    }
    r_prev->out_file = strdup(fifo);
    r_next->in_file = strdup(fifo);
    r_prev->is_out_pipe = 1;
    free(fifo);
  } else if (!r_prev->out_file) {
    // If the previous command doesn't have an output, don't output anything.
    r_prev->is_out_pipe = 1;
    r_prev->out_file = strdup("/dev/null");
  } else if (!r_next->in_file) {
    // If the next command doesn't have an input, don't take in anything.
    r_next->in_file = strdup("/dev/null");
  }
}

extern void freeCommand(Command command) {
  CommandRep r = command;

  if (r->pid != 0) {
    waitOnChild(r->pid);
    r->pid = 0;
  }

  char **argv = r->argv;
  while (*argv)
    free(*argv++);
  free(r->argv);
  free(r->in_file);
  free(r->out_file);
  free(r);
}

extern void freestateCommand() {
  if (cwd)
    free(cwd);
  if (owd)
    free(owd);
}
