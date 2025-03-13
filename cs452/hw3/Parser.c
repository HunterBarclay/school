#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Tree.h"
#include "Scanner.h"
#include "error.h"

/* Scanner to use */
static Scanner scan;

/* Custom error */
#undef ERROR
#define ERROR(s) ERRORLOC(__FILE__,__LINE__,"error","%s (pos: %d)",s,posScanner(scan))

/* Get next token */
static char *next()       { return nextScanner(scan); }
/* Get current token */
static char *curr()       { return currScanner(scan); }
/* Compare current token with string */
static int   cmp(char *s) { return cmpScanner(scan,s); }
/* Try to consume a token matching provided string */
static int   eat(char *s) { return eatScanner(scan,s); }

/* Parse word */
static T_word p_word();
/* Parse words */
static T_words p_words();
/* Parse redirection */
static T_redir p_redir();
/* Parse command */
static T_command p_command();
/* Parse pipeline */
static T_pipeline p_pipeline();
/* Parse sequence */
static T_sequence p_sequence();

static T_word p_word() {
  char *s=curr();
  if (!s)
    return 0;
  T_word word=new_word();
  word->s=strdup(s);
  next();
  return word;
}

static T_words p_words() {
  T_word word=p_word();
  if (!word)
    return 0;
  T_words words=new_words();
  words->word=word;
  if (cmp("|") || cmp("&") || cmp(";") || cmp("<") || cmp(">"))
    return words;
  words->words=p_words();
  return words;
}

static T_redir p_redir() {
  T_redir redir = new_redir();
  if (eat("<")) {
    redir->in_word = p_word();
  }
  if (eat(">")) {
    redir->out_word = p_word();
  }
  return redir;
}

static T_command p_command() {
  T_words words = 0;
  words = p_words();
  if (!words)
    return 0;
  T_command command = new_command();
  command->words = words;
  command->redir = p_redir();

  return command;
}

static T_pipeline p_pipeline() {
  T_command command=p_command();
  if (!command)
    return 0;
  T_pipeline pipeline=new_pipeline();
  pipeline->command=command;
  if (eat("|"))
    pipeline->pipeline=p_pipeline();
  return pipeline;
}

static T_sequence p_sequence() {
  T_pipeline pipeline=p_pipeline();
  if (!pipeline)
    return 0;
  T_sequence sequence=new_sequence();
  sequence->pipeline=pipeline;
  if (eat("&")) {
    sequence->op="&";
    sequence->sequence=p_sequence();
  }
  if (eat(";")) {
    sequence->op=";";
    sequence->sequence=p_sequence();
  }
  return sequence;
}

extern Tree parseTree(char *s) {
  scan=newScanner(s);
  Tree tree=p_sequence();
  if (curr())
    ERROR("extra characters at end of input");
  freeScanner(scan);
  return tree;
}

/* Free word AST. */
static void f_word(T_word t);
/* Free words AST. */
static void f_words(T_words t);
/* Free redir AST. */
static void f_redir(T_redir t);
/* Free command AST */
static void f_command(T_command t);
/* Free pipeline AST. */
static void f_pipeline(T_pipeline t);
/* Free sequence AST. */
static void f_sequence(T_sequence t);

static void f_word(T_word t) {
  if (!t)
    return;
  if (t->s)
    free(t->s);
  free(t);
}

static void f_words(T_words t) {
  if (!t)
    return;
  f_word(t->word);
  f_words(t->words);
  free(t);
}

static void f_redir(T_redir t) {
  if (!t)
    return;
  f_word(t->in_word);
  f_word(t->out_word);
  free(t);
}

static void f_command(T_command t) {
  if (!t)
    return;
  f_redir(t->redir);
  f_words(t->words);
  free(t);
}

static void f_pipeline(T_pipeline t) {
  if (!t)
    return;
  f_command(t->command);
  f_pipeline(t->pipeline);
  free(t);
}

static void f_sequence(T_sequence t) {
  if (!t)
    return;
  f_pipeline(t->pipeline);
  f_sequence(t->sequence);
  free(t);
}

extern void freeTree(Tree t) {
  f_sequence(t);
}
