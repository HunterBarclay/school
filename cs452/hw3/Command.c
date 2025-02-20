#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Command.h"
#include "error.h"

typedef struct {
  char *file;
  char **argv;
  char *in_file;
  char *out_file;
} * CommandRep;

#define BIARGS CommandRep r, int *eof, Jobs jobs
#define BINAME(name) bi_##name
#define BIDEFN(name) static void BINAME(name)(BIARGS)
#define BIENTRY(name)                                                          \
  { #name, BINAME(name) }

static char *owd = 0;
static char *cwd = 0;

static void builtin_args(CommandRep r, int n) {
  char **argv = r->argv;
  for (n++; *argv++; n--)
    ;
  if (n)
    ERROR("wrong number of arguments to builtin command"); // warn
}

BIDEFN(exit) {
  builtin_args(r, 0);
  *eof = 1;
}

BIDEFN(pwd) {
  builtin_args(r, 0);
  if (!cwd)
    cwd = getcwd(0, 0);
  printf("%s\n", cwd);
}

BIDEFN(cd) {
  builtin_args(r, 1);
  if (strcmp(r->argv[1], "-") == 0) {
    char *twd = cwd;
    cwd = owd;
    owd = twd;
  } else {
    if (owd)
      free(owd);
    owd = cwd;
    cwd = strdup(r->argv[1]);
  }
  if (cwd && chdir(cwd))
    ERROR("chdir() failed"); // warn
}

static int builtin(BIARGS) {
  typedef struct {
    char *s;
    void (*f)(BIARGS);
  } Builtin;
  static const Builtin builtins[] = {
      BIENTRY(exit), BIENTRY(pwd), BIENTRY(cd), {0, 0}};
  int i;
  for (i = 0; builtins[i].s; i++)
    if (!strcmp(r->file, builtins[i].s)) {
      builtins[i].f(r, eof, jobs);
      return 1;
    }
  return 0;
}

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
    r->in_file = command->redir->in_word->s;
  else
    r->in_file = NULL;
  if (command->redir->out_word)
    r->out_file = command->redir->out_word->s;
  else
    r->out_file = NULL;
  return r;
}

static void child(CommandRep r, int fg) {
  int eof = 0;
  Jobs jobs = newJobs();

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
    int out_fd = open(r->out_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if (out_fd == -1) {
      ERROR("Failed to open output file.");
    }
    if (dup2(out_fd, STDOUT_FILENO) == -1) {
      ERROR("Failed to redirect standard output.");
    }
  }

  if (builtin(r, &eof, jobs))
    return;
  execvp(r->argv[0], r->argv);
  ERROR("execvp() failed");
  exit(0);
}

static int waitOnChild(int pid) {
  int stat;
  waitpid(pid, &stat, 0);
  return WEXITSTATUS(stat);
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

  if (fg)
    waitOnChild(pid);
}

extern void freeCommand(Command command) {
  CommandRep r = command;
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
