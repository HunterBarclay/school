#include "deq/deq.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Pipeline.h"
#include "error.h"
#include "Utils.h"

typedef struct {
  Deq processes;
  int fg; // not "&"
  int pid;
} * PipelineRep;

extern Pipeline newPipeline(int fg) {
  PipelineRep r = (PipelineRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");
  r->processes = deq_new();
  r->fg = fg;
  r->pid = 0;
  return r;
}

extern void addPipeline(Pipeline pipeline, Command command) {
  PipelineRep r = (PipelineRep)pipeline;

  // Get tail command. If tail has no out file, create a pipe between
  // current tail and next command
  if (deq_len(r->processes) != 0) {
    Command prev = (Command)deq_tail_ith(r->processes, 0);
    pipeCommand(prev, command);
  }

  deq_tail_put(r->processes, command);
}

extern int sizePipeline(Pipeline pipeline) {
  PipelineRep r = (PipelineRep)pipeline;
  return deq_len(r->processes);
}

static void execute(Pipeline pipeline, Jobs jobs, int *jobbed, int *eof) {
  PipelineRep r = (PipelineRep)pipeline;
  for (int i = 0; i < sizePipeline(r) && !*eof; i++)
    execCommand(deq_head_ith(r->processes, i), pipeline, jobs, jobbed, eof,
                r->fg);
}

extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof) {
  PipelineRep r = (PipelineRep)pipeline;
  int jobbed = 0;
  
  if (r->fg) {
    execute(pipeline, jobs, &jobbed, eof);
    if (!jobbed)
      freePipeline(pipeline);
    else
      waitOnJobs(jobs);
  } else {
    int pid = fork();
    if (pid == -1) {
      ERROR("Failed to fork pipeline.");
    } else if (pid == 0) {
      fprintf(stderr, "[+] %d\n", getpid());
      execute(pipeline, jobs, &jobbed, eof);
      freePipeline(pipeline);
      fprintf(stderr, "[-] %d\n", getpid());
      exit(0);
    }
    
    r->pid = pid;
    addJobs(jobs, pipeline);
  }

  // if (!jobbed)
}

extern void freePipeline(Pipeline pipeline) {
  PipelineRep r = (PipelineRep)pipeline;

  if (r->pid != 0) {
    waitOnChild(r->pid);
    r->pid = 0;
  }

  deq_del(r->processes, freeCommand);
  free(r);
}
