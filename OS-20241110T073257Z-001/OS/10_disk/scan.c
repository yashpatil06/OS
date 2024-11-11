#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDERS 200

// Function to perform SCAN disk scheduling
void scan(int requests[], int n, int head, int total_cylinders)
{
    int seek_count = 0;
    int initial = head;
    int current_position = head;

    // Sort the requests array in ascending order
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Print initial position
    printf("SCAN Disk Scheduling:\n");
    printf("Starting From: %d\n", initial);

    // First service requests greater than or equal to the current head position
    int i = 0;
    while (i < n && requests[i] < current_position)
    {
        i++;
    }

    // Move right (towards the end)
    for (int j = i; j < n; j++)
    {
        seek_count += abs(current_position - requests[j]);
        current_position = requests[j];
        printf("Head moved to: %d\n", current_position);
    }

    // Move to the end of the disk if needed
    if (current_position < total_cylinders - 1)
    {
        seek_count += abs(current_position - (total_cylinders - 1));
        current_position = total_cylinders - 1;
        printf("Head moved to: %d\n", current_position);
    }

    // Move left (reverse direction)
    for (int j = i - 1; j >= 0; j--)
    {
        seek_count += abs(current_position - requests[j]);
        current_position = requests[j];
        printf("Head moved to: %d\n", current_position);
    }

    // Print the total and average seek time
    printf("Total seek time : %d\n", seek_count);
    printf("Average seek time : %f\n", (float)seek_count / n);
}

// Main function to execute the SCAN algorithm
int main()
{
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 50;
    int total_cylinders = MAX_CYLINDERS;

    // Call the SCAN function with the request array, number of requests, initial head position, and total cylinders
    scan(requests, n, initial_head, total_cylinders);
    return 0;
}
