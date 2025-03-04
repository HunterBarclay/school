#include "Utils.h"

#include <sys/wait.h>

extern int waitOnChild(int pid) {
  int stat;
  waitpid(pid, &stat, 0);
  return WEXITSTATUS(stat);
}