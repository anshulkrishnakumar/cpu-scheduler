#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;

    int remaining; // for round robin
} Process;

void fcfs(Process *p, int n);
void round_robin(Process *p, int n, int quantum);
void print_results(Process p[], int n);
void print_gantt(Process p[], int n);

int main() {
    Process *p;
    int n = 3; // 3 processes
    int quantum = 2; // for round robin
    p = malloc(n * sizeof(Process));
    p[0] = (Process){1, 0, 4, 0, 0, 0, 4};
    p[1] = (Process){2, 1, 3, 0, 0, 0, 3};
    p[2] = (Process){3, 2, 1, 0, 0, 0, 1};
    
    fcfs(p, n);
    //round_robin(p, n, quantum);
    print_results(p, n);
    print_gantt(p, n);
    

    free(p);
    return 0;
}

void fcfs(Process p[], int n) {
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) {
            time = p[i].arrival;            
        }
        time += p[i].burst;
        p[i].completion = time; // time at which it finishes
        p[i].turnaround = p[i].completion - p[i].arrival; // time spend in the system
        p[i].waiting = p[i].turnaround - p[i].burst; // time spent waiting for execution

    }
}

void round_robin(Process *p, int n, int quantum) {
    int time = 0;
    int done;

    do {
        done = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                done = 0;

                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].remaining = 0;

                    p[i].completion = time;
                }
            }
        }
    } while (!done);

    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void print_results(Process *p, int n) {
    float total_wt = 0, total_tat = 0, total_bt = 0;
    printf("\n\t\tID\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].id,
            p[i].arrival,
            p[i].burst,
            p[i].completion,
            p[i].waiting,
            p[i].turnaround);
        
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
        total_bt += p[i].burst;
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    float total_time = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].completion > total_time) {
            total_time = p[i].completion;
        }
    }

    float cpu_util = (total_bt / total_time) * 100;

    printf("\nAverage waiting time: %0.2f", avg_wt);
    printf("\nAverage turnaround time: %0.2f", avg_tat);
    printf("\nCPU utilization: %0.2f\n\n", cpu_util);
}

void print_gantt(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Process %d | ", p[i].id);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("\t\t  %d\t", p[i].completion);
    }
    printf("\n");
}