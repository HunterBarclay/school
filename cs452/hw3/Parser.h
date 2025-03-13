#ifndef PARSER_H
#define PARSER_H

/* External Tree object */
typedef void *Tree;

/**
 * Parse the AST from a string which (presumably) contains at least one sequence.
 */
extern Tree parseTree(char *s);

/**
 * Free the AST.
 */
extern void freeTree(Tree t);

#endif
