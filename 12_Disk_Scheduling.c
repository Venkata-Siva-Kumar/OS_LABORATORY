#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void FCFS(int arr[], int n, int head) 
{
    int total = 0;
    printf("\nFCFS Sequence: %d ", head);
    for (int i = 0; i < n; i++) 
    {
        printf("-> %d ", arr[i]);
        total += abs(arr[i] - head);
        head = arr[i];
    }
    printf("\nTotal Head Movement = %d\n", total);
}

void SSTF(int arr[], int n, int head) 
{
    int total = 0, completed[n], count = 0;
    for (int i = 0; i < n; i++) 
        completed[i] = 0;

    printf("\nSSTF Sequence: %d ", head);
    while (count < n) {
        int min = 1e9, pos = -1;
        for (int i = 0; i < n; i++) 
        {
            if (!completed[i]) 
            {
                int diff = abs(arr[i] - head);
                if (diff < min) 
                {
                    min = diff;
                    pos = i;
                }
            }
        }
        completed[pos] = 1;
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", arr[pos]);
        count++;
    }
    printf("\nTotal Head Movement = %d\n", total);
}

void SCAN(int arr[], int n, int head, int disk_size, int direction) 
{
    int total = 0;
    int left[n], right[n], l = 0, r = 0;
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] < head)
            left[l++] = arr[i];
        else
            right[r++] = arr[i];
    }
    left[l++] = 0;         // end of disk
    right[r++] = disk_size - 1;

    // Sort
    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (left[i] > left[j]) 
            {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
    for (int i = 0; i < r - 1; i++)
        for (int j = i + 1; j < r; j++)
            if (right[i] > right[j]) 
            {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    printf("\nSCAN Sequence: %d ", head);
    if (direction == 1) 
    { // moving right
        for (int i = 0; i < r; i++) 
        {
            printf("-> %d ", right[i]);
            total += abs(right[i] - head);
            head = right[i];
        }
        for (int i = l - 1; i >= 0; i--) 
        {
            printf("-> %d ", left[i]);
            total += abs(left[i] - head);
            head = left[i];
        }
    } 
    else 
    {
        for (int i = l - 1; i >= 0; i--) 
        {
            printf("-> %d ", left[i]);
            total += abs(left[i] - head);
            head = left[i];
        }
        for (int i = 0; i < r; i++) 
        {
            printf("-> %d ", right[i]);
            total += abs(right[i] - head);
            head = right[i];
        }
    }
    printf("\nTotal Head Movement = %d\n", total);
}



int main() 
{
    int n, head, disk_size, direction;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++) 
        scanf("%d", &arr[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter head direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    FCFS(arr, n, head);
    SSTF(arr, n, head);
    SCAN(arr, n, head, disk_size, direction);


    return 0;
}