#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef enum {
    READY,
    RUNNING,
    FINISHED,
} State;

typedef struct {
    int id;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;

    int remaining; // for round robin
    State state;
} Process;

void fcfs(Process *p, int n);
void round_robin(Process *p, int n, int quantum);
void print_results(Process *p, int n, float *avg_wt, float *avg_tat);

#endif