#include <stdio.h>

int main() 
{
    int frames[10], pages[30];
    int frameCount, pageCount, pageFaults = 0;
    int i, j, k = 0, flag;

    printf("Enter the number of pages: ");
    scanf("%d", &pageCount);

    printf("Enter the page reference string:\n");
    for (i = 0; i < pageCount; i++)
        scanf("%d", &pages[i]);

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    // Initialize all frames to -1 (empty)
    for (i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\nPage\tFrames\t\tPage Fault\n");
    printf("----------------------------------------\n");

    for (i = 0; i < pageCount; i++) 
    {
        flag = 0;

        // Check if page already exists in any frame
        for (j = 0; j < frameCount; j++) 
        {
            if (frames[j] == pages[i]) 
            {
                flag = 1; // Page hit
                break;
            }
        }

        // If page not found (page fault)
        if (flag == 0) 
        {
            frames[k] = pages[i];
            k = (k + 1) % frameCount; // Circular replacement
            pageFaults++;
        }

        // Display current status of frames
        printf("%d\t", pages[i]);
        for (j = 0; j < frameCount; j++) 
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }

        if (flag == 0)
            printf("\t\tYes");
        else
            printf("\t\tNo");

        printf("\n");
    }

    printf("----------------------------------------\n");
    printf("Total Page Faults = %d\n", pageFaults);

    return 0;
}
