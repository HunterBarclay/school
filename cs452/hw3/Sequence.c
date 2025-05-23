#include "deq/deq.h"

#include "Sequence.h"
#include "error.h"

extern Sequence newSequence() {
  return deq_new();
}

extern void addSequence(Sequence sequence, Pipeline pipeline) {
  deq_tail_put(sequence,pipeline);
}

extern void freeSequence(Sequence sequence) {
  deq_del(sequence,freePipeline);
}

extern void execSequence(Sequence sequence, Jobs jobs, int *eof) {
  while (deq_len(sequence) && !*eof) {
    execPipeline(deq_head_get(sequence),jobs,eof);
  }

  freeSequence(sequence); // Only frees pipelines that are left over after exit.
}
