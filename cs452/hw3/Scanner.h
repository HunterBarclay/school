#ifndef SCANNER_H
#define SCANNER_H

/* External Scanner objects */
typedef void *Scanner;

/**
 * Create a new scanner for the given character sequence.
 */
extern Scanner newScanner(char *s);

/**
 * Free scanner.
 */
extern void freeScanner(Scanner scan);

/**
 * Get next token from scanner.
 */
extern char *nextScanner(Scanner scan);

/**
 * Get current token from scanner.
 */
extern char *currScanner(Scanner scan);

/**
 * Compare current token with string.
 */
extern int cmpScanner(Scanner scan, char *s);

/**
 * Eat token if token matches string.
 */
extern int eatScanner(Scanner scan, char *s);

/**
 * Position of scanner.
 */
extern int posScanner(Scanner scan);

#endif
