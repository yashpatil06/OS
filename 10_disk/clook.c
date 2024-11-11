#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDERS 200

// Function to implement C-LOOK disk scheduling
void clook(int requests[], int n, int head)
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

	// Print initial status
	printf("C-LOOK Disk Scheduling:\n");
	printf("Starting From: %d\n", initial);

	// Traverse from the current head position to the right (higher cylinder requests)
	int i;
	for (i = 0; i < n; i++)
	{
		if (requests[i] >= current_position)
		{
			break;
		}
	}

	// Service requests to the right of the current head position
	for (int j = i; j < n; j++)
	{
		seek_count += abs(current_position - requests[j]);
		current_position = requests[j];
		printf("Head moved to: %d\n", current_position);
	}

	// Jump to the lowest request (C-LOOK jump) if the current position is not at the lowest
	if (i > 0)
	{
		seek_count += abs(current_position - requests[0]);
		current_position = requests[0];
		printf("Head moved to: %d\n", current_position);
	}

	// Service the remaining requests from the lowest to the initial break point
	for (int j = 1; j < i; j++)
	{ // Start from 1 to avoid moving to the lowest request again
		seek_count += abs(current_position - requests[j]);
		current_position = requests[j];
		printf("Head moved to: %d\n", current_position);
	}

	// Print total seek time
	printf("Total seek time (C-LOOK): %d\n\n", seek_count);
}

int main()
{
	int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
	int n = sizeof(requests) / sizeof(requests[0]);
	int initial_head = 50;

	clook(requests, n, initial_head);
	return 0;
}
