#include <stdio.h>

// Function to find the Least Recently Used (LRU) page
int findLRU(int time[], int n) 
{
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) 
    {
        if (time[i] < minimum) 
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() 
{
    int frames[10], pages[30], time[10];
    int totalFrames, totalPages;
    int counter = 0, flag1, flag2, i, j, pos, faults = 0;

    // Input total number of frames
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);

    // Input total number of pages
    printf("Enter total number of pages: ");
    scanf("%d", &totalPages);

    // Input page reference string
    printf("Enter page reference string: ");
    for (i = 0; i < totalPages; ++i)
        scanf("%d", &pages[i]);

    // Initialize frames to empty (-1)
    for (i = 0; i < totalFrames; ++i)
        frames[i] = -1;

    printf("\nPage\tFrames\t\tFault\n");
    printf("----------------------------------------\n");

    for (i = 0; i < totalPages; ++i) 
    {
        flag1 = flag2 = 0;

        // Check if page is already present (Page Hit)
        for (j = 0; j < totalFrames; ++j) 
        {
            if (frames[j] == pages[i]) 
            {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page not found (Empty frame available)
        if (flag1 == 0) 
        {
            for (j = 0; j < totalFrames; ++j) 
            {
                if (frames[j] == -1) 
                {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If all frames are full, replace the LRU page
        if (flag2 == 0) 
        {
            pos = findLRU(time, totalFrames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Display current frame contents
        printf("%d\t", pages[i]);
        for (j = 0; j < totalFrames; ++j) 
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }

        printf("\t");
        if (flag1 == 0)
            printf("Page Fault");
        else
            printf("No Fault");
        printf("\n");
    }

    printf("----------------------------------------\n");
    printf("Total Page Faults = %d\n", faults);

    return 0;
}
