#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "Jobs.h"
#include "Parser.h"
#include "Interpreter.h"
#include "error.h"

/**
 * Tasks:
 * [x] - Foreground Commands
 * [x] - Sequence of Commands
 * [x] - I/O Redirection
 * [x] - Background Commands
 * [x] - Pipelines
 * [x] - Remaining Builtin Commands
 */

/**
 * Main shell execution loop
 */
int main() {
  int eof=0;
  Jobs jobs=newJobs();
  char *prompt=0;
  srand(time(NULL));

  if (isatty(fileno(stdin))) {
    using_history();
    read_history(".history");
    prompt="$ ";
  } else {
    rl_bind_key('\t',rl_insert);
    rl_outstream=fopen("/dev/null","w");
  }
  
  while (!eof) {
    char *line=readline(prompt);
    if (!line)
      break;
    if (*line)
      add_history(line);
    Tree tree=parseTree(line);
    free(line);
    interpretTree(tree,&eof,jobs);
    freeTree(tree);
  }

  freeJobs(jobs);

  if (isatty(fileno(stdin))) {
    write_history(".history");
    rl_clear_history();
  } else {
    fclose(rl_outstream);
  }
  freestateCommand();
  return 0;
}
