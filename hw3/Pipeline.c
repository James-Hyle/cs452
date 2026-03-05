#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Pipeline.h"
#include "deq.h"
#include "error.h"

typedef struct {
  Deq processes;
  int fg; // not "&"
} *PipelineRep;

extern Pipeline newPipeline(int fg) {
  PipelineRep r = (PipelineRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");
  r->processes = deq_new();
  r->fg = fg;
  return r;
}

extern void addPipeline(Pipeline pipeline, Command command) {
  PipelineRep r = (PipelineRep)pipeline;
  deq_tail_put(r->processes, command);
}

extern int sizePipeline(Pipeline pipeline) {
  PipelineRep r = (PipelineRep)pipeline;
  return deq_len(r->processes);
}

static void execute(Pipeline pipeline, Jobs jobs, int *jobbed, int *eof) {
  PipelineRep r = (PipelineRep)pipeline;
  int n = sizePipeline(r);
  if (n == 0)
    return;

  int pips[n - 1][2];

  for (int i = 0; i < n - 1; i++) {
    if (pipe(pips[i]) == -1)
      ERROR("pipe() failed");
  }

  for (int i = 0; i < n && !*eof; i++) {
    int in_fd = (i == 0) ? STDIN_FILENO : pips[i - 1][0];
    int out_fd = (i == n - 1) ? STDOUT_FILENO : pips[i][1];

    execCommand(deq_head_ith(r->processes, i), pipeline, jobs, jobbed, eof,
                r->fg, in_fd, out_fd);
  }

  for (int i = 0; i < n - 1; i++) {
    close(pips[i][0]);
    close(pips[i][1]);
  }

  for (int i = 0; i < n; i++)
    wait(NULL);

  if (!*jobbed)
    addJobs(jobs, pipeline);
}

extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof) {
  int jobbed = 0;
  execute(pipeline, jobs, &jobbed, eof);
  if (!jobbed)
    freePipeline(pipeline); // for fg builtins, and such
}

extern void freePipeline(Pipeline pipeline) {
  PipelineRep r = (PipelineRep)pipeline;
  deq_del(r->processes, freeCommand);
  free(r);
}
