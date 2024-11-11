#include <stdio.h>	// Include the standard I/O library for input/output functions
#include <stdlib.h> // Include the standard library for functions like abs()

#define MAX_CYLINDERS 200 // Define a constant for the maximum number of cylinders

// Function to perform SSTF (Shortest Seek Time First) disk scheduling
void sstf(int requests[], int n, int head)
{
	int completed[MAX_CYLINDERS] = {0}; // Array to keep track of completed requests, initialized to 0
	int seek_count = 0;					// Variable to keep track of total seek time
	int current_position = head;		// Variable to store the current position of the disk head

	// Print the starting message for SSTF disk scheduling
	printf("SSTF Disk Scheduling:\n");

	// Loop through all the requests until they are all processed
	for (int i = 0; i < n; i++)
	{
		int min_distance = 9999; // Initialize the minimum distance to a very large value
		int index = -1;			 // Index to store the closest request's index

		// Find the request with the shortest distance from the current position
		for (int j = 0; j < n; j++)
		{
			if (!completed[j])
			{														// Check if the request has not been completed
				int distance = abs(requests[j] - current_position); // Calculate the absolute distance

				// Update minimum distance and index if a closer request is found
				if (distance < min_distance)
				{
					min_distance = distance;
					index = j;
				}
			}
		}

		// Mark the selected request as completed
		completed[index] = 1;

		// Add the minimum distance to the total seek time
		seek_count += min_distance;

		// Move the disk head to the position of the closest request
		current_position = requests[index];

		// Print the current position of the disk head
		printf("Head moved to: %d\n", current_position);
	}

	// Print the total seek time after completing all requests
	printf("Total seek time (SSTF): %d\n\n", seek_count);
}

// Main function to execute the SSTF algorithm
int main()
{
	int requests[] = {98, 183, 37, 122, 14, 124, 65, 67}; // Array of disk I/O requests
	int n = sizeof(requests) / sizeof(requests[0]);		  // 8     // Calculate the number of requests
	int initial_head = 50;								  // Initial position of the disk head
	int total_cylinders = MAX_CYLINDERS;				  // Total number of cylinders (unused)

	// Call the SSTF function with the request array, number of requests, and initial head position
	sstf(requests, n, initial_head);

	// Return 0 to indicate successful program termination
	return 0;
}
