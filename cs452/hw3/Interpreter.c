#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Interpreter.h"
#include "Sequence.h"
#include "Pipeline.h"
#include "Command.h"

/**
 * Interpret a command from the AST.
 */
static Command i_command(T_command t);

/**
 * Interpret a pipeline from the AST.
 */
static void i_pipeline(T_pipeline t, Pipeline pipeline);

/**
 * Interpret a sequence from the AST.
 */
static void i_sequence(T_sequence t, Sequence sequence);

static Command i_command(T_command t) {
  if (!t)
    return 0;
  Command command=0;
  if (t->words)
    command=newCommand(t);
  return command;
}

static void i_pipeline(T_pipeline t, Pipeline pipeline) {
  if (!t)
    return;
  addPipeline(pipeline,i_command(t->command));
  i_pipeline(t->pipeline,pipeline);
}

static void i_sequence(T_sequence t, Sequence sequence) {
  if (!t)
    return;
  Pipeline pipeline=newPipeline(t->op ? strcmp(";", t->op) == 0 : 1);
  i_pipeline(t->pipeline,pipeline);
  addSequence(sequence,pipeline);
  i_sequence(t->sequence,sequence);
}

extern void interpretTree(Tree t, int *eof, Jobs jobs) {
  if (!t)
    return;
  Sequence sequence=newSequence();
  i_sequence(t,sequence);
  execSequence(sequence,jobs,eof);
}
