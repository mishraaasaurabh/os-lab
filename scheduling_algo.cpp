#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int rt;
    int pr;
} Process;

void findWaitingTime(Process p[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnaroundTime(Process p[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(Process p[], int n, int bt[]) {
    int wt[MAX], tat[MAX];
    findWaitingTime(p, n, bt, wt);
    findTurnaroundTime(p, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", (float)total_tat / n);
}

void FCFS(Process p[], int n) {
    int bt[MAX];
    for (int i = 0; i < n; i++) {
        bt[i] = p[i].bt;
    }
    findAvgTime(p, n, bt);
}

void RoundRobin(Process p[], int n, int quantum) {
    int bt[MAX], wt[MAX], tat[MAX], completed = 0, time = 0;

    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    printf("\nRound Robin Scheduling\n");
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                if (p[i].rt > quantum) {
                    time += quantum;
                    p[i].rt -= quantum;
                } else {
                    time += p[i].rt;
                    p[i].wt = time - p[i].bt;
                    p[i].tat = p[i].wt + p[i].bt;
                    completed++;
                    p[i].rt = 0;
                }
            }
        }
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
}

void PriorityScheduling(Process p[], int n) {
    Process temp;
    int bt[MAX], wt[MAX], tat[MAX];

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].pr > p[j].pr) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    findAvgTime(p, n, bt);
}

void ShortestJobFirst(Process p[], int n) {
    Process temp;
    int bt[MAX], wt[MAX], tat[MAX];

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].bt > p[j].bt) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    findAvgTime(p, n, bt);
}

int main() {
    int n, i, choice, quantum;
    Process p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter priority for process %d: ", p[i].pid);
        scanf("%d", &p[i].pr);
    }

    printf("\nCPU Scheduling Algorithms:\n");
    printf("1. FCFS\n");
    printf("2. Round Robin\n");
    printf("3. Priority-based\n");
    printf("4. Shortest Job First\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(p, n);
            break;
        case 2:
            printf("Enter quantum time: ");
            scanf("%d", &quantum);
            RoundRobin(p, n, quantum);
            break;
        case 3:
            PriorityScheduling(p, n);
            break;
        case 4:
            ShortestJobFirst(p, n);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
