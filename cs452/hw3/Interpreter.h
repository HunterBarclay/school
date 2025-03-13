#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"
#include "Tree.h"
#include "Jobs.h"

/**
 * Interpret a parsed AST.
 */
extern void interpretTree(Tree t, int *eof, Jobs jobs);

#endif
