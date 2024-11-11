#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frames[][MAX_FRAMES], int pageCount, int frameCount)
{
    printf("Frames:\n");
    for (int j = 0; j < frameCount; j++)
    {
        printf("Frame %d: ", j + 1);
        for (int i = 0; i < pageCount; i++)
        {
            if (frames[i][j] != -1)
            {
                printf("[%d] ", frames[i][j]);
            }
            else
            {
                printf("[ ] "); // Empty frame
            }
        }
        printf("\n");
    }
    printf("\n");
}

void lru(int pages[], int pageCount, int frameCount)
{
    int frames[MAX_PAGES][MAX_FRAMES];
    for (int i = 0; i < pageCount; i++)
        for (int j = 0; j < frameCount; j++)
            frames[i][j] = -1; // Initialize frames to -1 for empty slots

    int pageFaults = 0;

    for (int i = 0; i < pageCount; i++)
    {
        int found = 0;
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[i][j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            int lruIndex = -1, lruTime = -1;
            for (int j = 0; j < frameCount; j++)
            {
                if (frames[i][j] == -1)
                {
                    lruIndex = j;
                    break;
                }
                int lastUsed = -1;
                for (int k = i - 1; k >= 0; k--)
                {
                    if (pages[k] == frames[i][j])
                    {
                        lastUsed = k;
                        break;
                    }
                }
                if (lastUsed < lruTime || lruTime == -1)
                {
                    lruTime = lastUsed;
                    lruIndex = j;
                }
            }
            frames[i][lruIndex] = pages[i];
            pageFaults++;
        }

        // Copy current frame state to the next row
        if (i < pageCount - 1)
        {
            for (int k = 0; k < frameCount; k++)
            {
                frames[i + 1][k] = frames[i][k];
            }
        }
    }
    printFrames(frames, pageCount, frameCount);
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

int main()
{
    int pages[MAX_PAGES];
    int pageCount, frameCount;

    printf("Enter number of pages: ");
    scanf("%d", &pageCount);
    printf("Enter page numbers: ");
    for (int i = 0; i < pageCount; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    lru(pages, pageCount, frameCount);

    return 0;
}