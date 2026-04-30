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
void print_results(Process *p, int n, float *avg_wt, float *avg_tat);

int main() {
    float fcfs_wt, fcfs_tat;
    float rr_wt, rr_tat;
    int n = 3; // 3 processes
    Process *p_fcfs = malloc(n * sizeof(Process));
    Process *p_rr = malloc(n * sizeof(Process));

    int quantum = 2; // for round robin
    p_fcfs[0] = (Process){1, 0, 4, 0, 0, 0, 4};
    p_fcfs[1] = (Process){2, 1, 3, 0, 0, 0, 3};
    p_fcfs[2] = (Process){3, 2, 1, 0, 0, 0, 1};
    
    for (int i = 0; i < n; i++) {
        p_rr[i] = p_fcfs[i];
    }

    fcfs(p_fcfs, n);
    round_robin(p_rr, n, quantum);

    printf("FCFS\n");
    print_results(p_fcfs, n, &fcfs_wt, &fcfs_tat);

    printf("RR\n");
    print_results(p_rr, n, &rr_wt, &rr_tat);

    float wt_change = ((fcfs_wt - rr_wt) / fcfs_wt) * 100;
    float tat_change = ((fcfs_tat - rr_tat) / fcfs_tat) * 100;

    printf("\n\t\tComparison\n"); // positive means RR is better, negative means RR is worse
    printf("Waiting time change:\t%0.2f%%\n", wt_change);
    printf("Turnaround time change:\t%0.2f%%\n\n", tat_change);
    
    free(p_fcfs);
    free(p_rr);
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

void print_results(Process *p, int n, float *avg_wt, float *avg_tat) {
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

    *avg_wt = total_wt / n;
    *avg_tat = total_tat / n;
    float total_time = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].completion > total_time) {
            total_time = p[i].completion;
        }
    }

    float cpu_util = (total_bt / total_time) * 100;

    printf("\nAverage waiting time: %0.2f", *avg_wt);
    printf("\nAverage turnaround time: %0.2f", *avg_tat);
    printf("\nCPU utilization: %0.2f\n\n", cpu_util);

}