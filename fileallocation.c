#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define BLOCK_SIZE 4
void displayBlocks(int *blockFlag, int n)
{
    printf("\n");
    int totalNumberOfFreeBlocks = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 3 == 0)
        {
            printf("\n");
        }
        printf("%d\t", blockFlag[i]);
        if (blockFlag[i] == -1)
        {
            totalNumberOfFreeBlocks += 1;
        }
    }
    printf("\nTotal available space = %d MB", totalNumberOfFreeBlocks * 4);
    printf("\nTotal occupied space = %d MB\n", (n - totalNumberOfFreeBlocks) * 4);
}
void addFile(int fileSize, int *blockFlag, int numberOfBlocks)
{
    int allocated = 0;
    int numberOfBlocksNeeded = fileSize / BLOCK_SIZE;
    int flag = 0;
    if (fileSize % BLOCK_SIZE != 0)
    {
        numberOfBlocksNeeded += 1;
    }
    for (int j = 0; j < numberOfBlocks; j++)
    {
        flag = 0;
        if (j + numberOfBlocksNeeded > numberOfBlocks)
        {
            break;
        }
        if (blockFlag[j] != -1)
        {
            continue;
        }
        for (int k = j + 1; k < numberOfBlocksNeeded + j; k++)
        {
            if (blockFlag[k] != -1)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\nAllocated blocks for file : ");
            for (int k = j; k < numberOfBlocksNeeded + j; k++)
            {
                printf("%d ", k);
                blockFlag[k] = 1;
            }
            allocated = 1;
            break;
        }
    }
    if (allocated == 0)
    {
        printf("\nNo space available for file");
    }
}
int main()
{
    int numberOfFiles;
    int numberOfBlocks;
    int flag = 0;
    printf("\nEnter the number of files:");
    scanf("%d", &numberOfFiles);
    printf("\nEnter the number of blocks:");
    scanf("%d", &numberOfBlocks);
    int *blockFlag;
    int *files;
    blockFlag = (int *)malloc(numberOfBlocks * sizeof(int));
    files = (int *)malloc(numberOfFiles * sizeof(int));
    memset(blockFlag,-1,numberOfBlocks*sizeof(blockFlag[0]));
    printf("\nEnter the size of each of the files:");
    for (int i = 0; i < numberOfFiles; i++)
    {
        printf("\nFile %d:", i + 1);
        scanf("%d", &files[i]);
    }
    
    for (int i = 0; i < numberOfFiles; i++)
    {
        int allocated = 0;
        int numberOfBlocksNeeded = files[i] / BLOCK_SIZE;
        if (files[i] % BLOCK_SIZE != 0)
        {
            numberOfBlocksNeeded += 1;
        }
        
        for (int j = 0; j < numberOfBlocks; j++)
        {
            flag = 0;
            if (j + numberOfBlocksNeeded > numberOfBlocks)
            {
                //printf("\nInside first if");
                break;
            }
            if (blockFlag[j] != -1)
            {
                continue;
            }
            //displayBlocks(blockFlag, numberOfBlocks);
            for (int k = j; k < numberOfBlocksNeeded + j; k++)
            {
                //printf("\nValue of k = %d\n ", k);
                if (blockFlag[k] != -1)
                {
                    //printf("\nInside inner for's first if\n");
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                printf("\nAllocated blocks for file %d: ", i + 1);
                for (int k = j; k < numberOfBlocksNeeded + j; k++)
                {
                    printf("%d ", k);
                    blockFlag[k] = 1;
                    
                }
                allocated = 1;
                break;
            }
        }
        if (allocated == 0)
        {
            printf("\nNo space available for file %d", i + 1);
        }
    }
    while (1)
    {
        printf("\n\n1. Add another file\n2. Display available space\n3. Exit\nEnter choice:");
        int choice, fileSize;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\nEnter the file size:");
            scanf("%d", &fileSize);
            addFile(fileSize, blockFlag, numberOfBlocks);
        }
        else if (choice == 2)
        {
            displayBlocks(blockFlag, numberOfBlocks);
        }
        else if (choice == 3)
        {
            printf("\nExiting . . .");
            exit(0);
        }
    }

    return 0;
}
