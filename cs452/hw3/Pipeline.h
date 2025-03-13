#ifndef PIPELINE_H
#define PIPELINE_H

/* External Pipeline object */
typedef void *Pipeline;

#include "Command.h"
#include "Jobs.h"

/**
 * Create new pipeline. Specify if it should be run in the foreground
 * or not.
 */
extern Pipeline newPipeline(int fg);

/**
 * Add command to the pipeline.
 */
extern void addPipeline(Pipeline pipeline, Command command);

/**
 * Get number of commands in the pipeline.
 */
extern int sizePipeline(Pipeline pipeline);

/**
 * Execute pipelines.
 */
extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof);

/**
 * Free the pipeline and its commands. Wait on pipeline children process
 * if one exists, and then free all commands.
 */
extern void freePipeline(Pipeline pipeline);

#endif
