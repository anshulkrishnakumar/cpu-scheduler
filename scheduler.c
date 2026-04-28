#include <stdio.h>

typedef struct {
    int id;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
} Process;

void fcfs(Process p[], int n);
void print_results(Process p[], int n);
void print_gantt(Process p[], int n);

int main() {
    Process p[] = {
        {1, 0, 4, 0, 0, 0},
        {2, 1, 3, 0, 0, 0},
        {3, 2, 1, 0, 0, 0}
    };

    int n = 3; // 3 processes
    
    fcfs(p, n);
    print_results(p, n);
    print_gantt(p, n);
    

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

void print_results(Process p[], int n) {
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
    float total_time = p[n - 1].completion;

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