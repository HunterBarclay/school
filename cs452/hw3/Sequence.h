#ifndef SEQUENCE_H
#define SEQUENCE_H

/* External Sequence objects */
typedef void *Sequence;

#include "Jobs.h"
#include "Pipeline.h"

/**
 * Create new sequence.
 */
extern Sequence newSequence();

/**
 * Add a new pipeline to the sequence.
 */
extern void addSequence(Sequence sequence, Pipeline pipeline);

/**
 * Free the sequence.
 */
extern void freeSequence(Sequence sequence);

/**
 * Execute the sequence.
 */
extern void execSequence(Sequence sequence, Jobs jobs, int *eof);

#endif
