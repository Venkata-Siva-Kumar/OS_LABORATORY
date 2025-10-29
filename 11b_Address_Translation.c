#include <stdio.h>
int main() 
{
    int pageNumber, offset, logicalAddress;
    int frameNumber;
    int pageTable[20];
    int pageSize, numPages, physicalAddress;
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    
    printf("Enter the page size (in bytes): ");
    scanf("%d", &pageSize);
    
    printf("Enter the page table (frame number for each page):\n");
    for (int i = 0; i < numPages; i++) 
    {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }
    printf("\nEnter the logical address (in decimal): ");
    scanf("%d", &logicalAddress);
    
    // Calculate page number and offset
    pageNumber = logicalAddress / pageSize;
    offset = logicalAddress % pageSize;
    if (pageNumber >= numPages || pageTable[pageNumber] == -1) 
    {
        printf("\nInvalid logical address or page not present in memory!\n");
    } 
    else 
    {
        frameNumber = pageTable[pageNumber];
        physicalAddress = (frameNumber * pageSize) + offset;
        printf("\n----- Address Translation -----\n");
        printf("Logical Address: %d\n", logicalAddress);
        printf("Page Number: %d\n", pageNumber);
        printf("Offset: %d\n", offset);
        printf("Frame Number (from page table): %d\n", frameNumber);
        printf("Physical Address: %d\n", physicalAddress);
        printf("--------------------------------\n");
    }
    return 0;
}