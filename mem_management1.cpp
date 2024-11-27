#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void first_fit(int blocks[], int block_size[], int n_blocks, int process_size[], int n_processes) {
    int allocation[MAX_PROCESSES];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n_processes; i++) {
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j] >= process_size[i]) {
                allocation[i] = j; // Allocate block j to process i
                blocks[j] -= process_size[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n_processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

void best_fit(int blocks[], int block_size[], int n_blocks, int process_size[], int n_processes) {
    int allocation[MAX_PROCESSES];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n_processes; i++) {
        int best_index = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j] >= process_size[i]) {
                if (best_index == -1 || blocks[j] < blocks[best_index])
                    best_index = j;
            }
        }
        if (best_index != -1) {
            allocation[i] = best_index;
            blocks[best_index] -= process_size[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n_processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

void worst_fit(int blocks[], int block_size[], int n_blocks, int process_size[], int n_processes) {
    int allocation[MAX_PROCESSES];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n_processes; i++) {
        int worst_index = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j] >= process_size[i]) {
                if (worst_index == -1 || blocks[j] > blocks[worst_index])
                    worst_index = j;
            }
        }
        if (worst_index != -1) {
            allocation[i] = worst_index;
            blocks[worst_index] -= process_size[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n_processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

int main() {
    int block_size[MAX_BLOCKS], process_size[MAX_PROCESSES];
    int n_blocks, n_processes;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &n_blocks);
    printf("Enter the size of each block:\n");
    for (int i = 0; i < n_blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block_size[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n_processes);
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &process_size[i]);
    }

    int blocks_first[MAX_BLOCKS], blocks_best[MAX_BLOCKS], blocks_worst[MAX_BLOCKS];
    memcpy(blocks_first, block_size, sizeof(block_size));
    memcpy(blocks_best, block_size, sizeof(block_size));
    memcpy(blocks_worst, block_size, sizeof(block_size));

    first_fit(blocks_first, block_size, n_blocks, process_size, n_processes);
    best_fit(blocks_best, block_size, n_blocks, process_size, n_processes);
    worst_fit(blocks_worst, block_size, n_blocks, process_size, n_processes);

    return 0;
}
