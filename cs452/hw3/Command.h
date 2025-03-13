#ifndef COMMAND_H
#define COMMAND_H

/* External Command object */
typedef void *Command;

#include "Tree.h"
#include "Jobs.h"
#include "Sequence.h"

/**
 * Creates new command from parsed command AST.
 */
extern Command newCommand(T_command command);

/**
 * Executes a command from a given pipeline. Adds pipeline to jobs when
 * a command is run in a child process. Can signal if the shell is to be exited.
 * 
 * All builtin commands run in the foreground are executed in the parent process.
 */
extern void execCommand(Command command, Pipeline pipeline, Jobs jobs,
			int *jobbed, int *eof, int fg);

/**
 * Pipeline two commands together. If previous command has an output file
 * specified, or if next command has an input file specified, non redirected
 * output and input will be sent to /dev/null. Otherwise, a pipeline will be
 * created in the tmp directory and both commands set to use said pipeline.
 */
extern void pipeCommand(Command prev, Command next);

/**
 * Free the command. This will wait for any child process stored within the command,
 * and free its structure.
 */
extern void freeCommand(Command command);

/**
 * Free heap allocated state data within the command module.
 */
extern void freestateCommand();

#endif
