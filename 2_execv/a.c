#include <stdio.h>      // Include standard input/output library for printf/scanf
#include <stdlib.h>     // Include standard library for functions like atoi()
#include <sys/types.h>  // Include library for data types like pid_t
#include <sys/wait.h>   // Include library for wait() function
#include <unistd.h>     // Include library for fork(), execv(), and getpid()

// Main function that accepts command-line arguments
void main(int argc, char *argv[]) {
    char *arr[argc];  // Array to hold the arguments passed to the program
    char *temp;       // Temporary variable for swapping during sorting
    int i, j, n, status;  // Loop variables and status for process handling
    pid_t pid;        // Variable to store process ID

    // Create a new process using fork
    pid = fork();

    // Copy command-line arguments into the arr array, excluding the program name
    for (i = 1; i < argc; i++) {
        arr[i - 1] = argv[i];  // Assign command-line arguments to arr
    }

    // Number of elements to sort (argc - 1 because the first argument is the program name)
    n = argc - 1;

    // Bubble Sort algorithm to sort the array of arguments in ascending numerical order
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            // Compare the integer values of arr[j] and arr[j + 1]
            if (atoi(arr[j]) > atoi(arr[j + 1])) {
                // Swap if the current element is greater than the next
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Null-terminate the array to prepare for execv()
    arr[argc - 1] = NULL;

    // If the process is the child process (pid == 0)
    if (pid == 0) {
        execv(arr[0], arr);  // Replace the child process with the program specified by arr[0]
    }
    else {
        // Parent process waits for the child to complete
        wait(&status);
        // Print the process ID of the parent
        printf("\nParent Id: %d", getpid());
    }
}
