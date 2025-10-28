#include <stdio.h>

void print(int n,int allocation[],int processSize[])
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
void firstFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1; // -1 means not allocated
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (blockSize[j] >= processSize[i]) 
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\nProcess No\tProcess Size\tBlock No\n");
    print(n,allocation,processSize);
}

void bestFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++) 
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) 
        {
            if (blockSize[j] >= processSize[i]) 
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) 
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\nProcess No\tProcess Size\tBlock No\n");
    print(n,allocation,processSize);
}

void worstFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++) 
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) 
        {
            if (blockSize[j] >= processSize[i]) 
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) 
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\nProcess No\tProcess Size\tBlock No\n");
    print(n,allocation,processSize);
}

int main() 
{
    int m, n;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSize[n];

    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    int block1[m], block2[m], block3[m];
    for (int i = 0; i < m; i++) {
    block1[i] = blockSize[i];
    block2[i] = blockSize[i];
    block3[i] = blockSize[i];
    }
    firstFit(block1, m, processSize, n);
    bestFit(block2, m, processSize, n);
    worstFit(block3, m, processSize, n);
    return 0;
}
