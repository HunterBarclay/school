#ifndef TREE_H
#define TREE_H

typedef struct T_sequence *T_sequence;
typedef struct T_pipeline *T_pipeline;
typedef struct T_command  *T_command;
typedef struct T_redir    *T_redir;
typedef struct T_words    *T_words;
typedef struct T_word     *T_word;

/* Sequence AST. */
struct T_sequence {
  T_pipeline pipeline;
  char *op;			/* ; or & */
  T_sequence sequence;
};

/* Pipeline AST. */
struct T_pipeline {
  T_command command;
  T_pipeline pipeline;
};

/* Command AST. */
struct T_command {
  T_words words;
  T_redir redir;
};

/* Redir AST. */
struct T_redir {
  T_word in_word;  // Word specifying input file.
  T_word out_word; // Word specifying output file.
};

/* Words AST. */
struct T_words {
  T_word word;
  T_words words;
};

/* Word AST. */
struct T_word {
  char *s;
};

/* Parse sequence */
extern T_sequence new_sequence();
/* Parse pipeline */
extern T_pipeline new_pipeline();
/* Parse command */
extern T_command  new_command();
/* Parse redir */
extern T_redir    new_redir();
/* Parse words */
extern T_words    new_words();
/* Parse word */
extern T_word     new_word();

#endif
