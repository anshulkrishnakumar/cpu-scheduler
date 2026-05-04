# CPU Scheduler

## Overview

This is a CPU scheduling simulator written in C.
It compares:

* FCFS (First Come First Serve)
* Round Robin

You can input processes and see how both algorithms perform.

---

## Features

* dynamic user input (number of processes, arrival time, burst time, quantum)
* FCFS scheduling
* Round Robin scheduling (queue-based)
* metrics:

  * completion time (CT)
  * waiting time (WT)
  * turnaround time (TAT)
  * CPU utilization
* comparison between FCFS and RR
* input validation
* header file structure
* enum-based process state tracking

---

## How to run

Compile:

```bash id="k39a2s"
gcc scheduler.c -o scheduler
```

Run:

```bash id="l20x7m"
./scheduler
```

On Windows:

```bash id="z8p1wr"
scheduler.exe
```

---

## Sample Input (how to enter it)

When you run the program, it will prompt you step-by-step.

Example:

```text id="u9e1ox"
Enter number of processes: 3
Enter time quantum: 2

Arrival time for P1: 0
Burst time for P1: 6

Arrival time for P2: 1
Burst time for P2: 2

Arrival time for P3: 2
Burst time for P3: 1
```

---

## What the results mean

For each process, you’ll see:

* **CT (Completion Time)** → when the process finishes
* **WT (Waiting Time)** → how long it waited before running
* **TAT (Turnaround Time)** → total time in the system (CT - AT)

At the bottom:

* **Average WT / TAT** → overall performance
* **CPU Utilization** → how busy the CPU was

---

## Comparison section

At the end, you’ll see something like:

```text id="j1n5vx"
Comparison
Waiting time change:     25.00%
Turnaround time change:  10.00%
```

### How to read it

* **Positive %**

  * Round Robin performed better
  * lower waiting / turnaround times

* **Negative %**

  * Round Robin performed worse
  * FCFS was better for that input

* **0%**

  * both algorithms performed the same

---

## What to expect

* FCFS tends to:

  * favor earlier processes
  * delay shorter jobs if they arrive later

* Round Robin tends to:

  * give all processes a fair share of CPU time
  * let shorter jobs finish earlier (depending on quantum)

Results will vary depending on:

* arrival times
* burst times
* chosen quantum
