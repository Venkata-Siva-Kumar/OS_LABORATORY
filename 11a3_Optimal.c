#include <stdio.h>

// Function to find the optimal page to replace
int findOptimal(int pages[], int frames[], int n, int index, int totalFrames) 
{
    int pos = -1, farthest = index, i, j, found;
    for (i = 0; i < totalFrames; ++i) 
    {
        found = 0;
        for (j = index; j < n; ++j) 
        {
            if (frames[i] == pages[j]) 
            {
                found = 1;
                if (j > farthest) 
                {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If a page is never used again, return it immediately
        if (found == 0)
            return i;
    }
    // If all pages are used again, replace the one used farthest in future
    return (pos == -1) ? 0 : pos;
}

int main() 
{
    int frames[10], pages[30];
    int totalFrames, totalPages, pageFaults = 0;
    int i, j, k, pos, flag1, flag2;

    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);

    printf("Enter total number of pages: ");
    scanf("%d", &totalPages);

    printf("Enter the page reference string: ");
    for (i = 0; i < totalPages; ++i)
        scanf("%d", &pages[i]);

    for (i = 0; i < totalFrames; ++i)
        frames[i] = -1;

    printf("\nPage\tFrames\t\tFault\n");
    printf("----------------------------------------\n");

    for (i = 0; i < totalPages; ++i) 
    {
        flag1 = flag2 = 0;

        // Check if page already exists in any frame (Page Hit)
        for (j = 0; j < totalFrames; ++j) 
        {
            if (frames[j] == pages[i]) 
            {
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page not found, try to load it into an empty frame
        if (flag1 == 0) 
        {
            for (j = 0; j < totalFrames; ++j) 
            {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    pageFaults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If all frames are full, replace the optimal page
        if (flag2 == 0) 
        {
            pos = findOptimal(pages, frames, totalPages, i + 1, totalFrames);
            frames[pos] = pages[i];
            pageFaults++;
        }

        // Print the current frame status
        printf("%d\t", pages[i]);
        for (k = 0; k < totalFrames; ++k) 
        {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }

        printf("\t");
        if (flag1 == 0)
            printf("Page Fault\n");
        else
            printf("No Fault\n");
    }

    printf("----------------------------------------\n");
    printf("Total Page Faults = %d\n", pageFaults);

    return 0;
}
