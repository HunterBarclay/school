#ifndef JOBS_H
#define JOBS_H

typedef void *Jobs;

#include "Pipeline.h"

/**
 * Queue for running jobs.
 */
extern Jobs newJobs();

/**
 * Add a pipeline to the jobs queue.
 */
extern void addJobs(Jobs jobs, Pipeline pipeline);

/**
 * Pop off and wait all jobs.
 */
extern void waitOnJobs(Jobs jobs);

/**
 * Get number of jobs in queue.
 */
extern int sizeJobs(Jobs jobs);

/**
 * Free the queue of jobs.
 */
extern void freeJobs(Jobs jobs);

#endif
