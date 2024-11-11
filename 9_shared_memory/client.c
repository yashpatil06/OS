#include <stdio.h>       // Standard I/O library for input/output operations
#include <stdlib.h>      // Standard library for system functions like system()
#include <sys/ipc.h>     // Header for IPC (Inter-Process Communication) mechanisms
#include <sys/shm.h>     // Header for shared memory functions

// Structure to hold data in shared memory
struct data {
    char s[100];  // Character array to store a string
    int flag;     // Integer flag used for signaling between processes
};

void main() {
    // Create a unique key for shared memory using ftok()
    key_t key = ftok("memory.txt", 'A');  // Generate an IPC key based on "memory.txt" and character 'A'

    // Create or access a shared memory segment of size 1024 bytes with read/write permissions
    int shmid = shmget(key, 1024, 0777 | IPC_CREAT);  // Create shared memory with key and permissions

    // Attach the shared memory segment to the process's address space
    struct data *d = shmat(shmid, NULL, 0);  // Attach shared memory to pointer `d`

    // Initialize the flag in the shared memory structure to 0 (indicating no data ready)
    d->flag = 0;

    // Wait until the flag in the shared memory is set to 1 (indicating data is ready)
    while (d->flag != 1) {
        printf("\nWaiting...");  // Print "Waiting..." to indicate the process is waiting for data
        sleep(2);                // Pause for 2 seconds before checking again
    }

    // Print the received data when the flag is set to 1
    printf("\nThe data sent is:");  // Print a message indicating data reception
    printf("%s", d->s);             // Print the string stored in the shared memory

    // Set the flag to -1 to signal the completion of data read
    d->flag = -1;

    // Display current shared memory segments using the `ipcs -m` system command
    system("ipcs -m");

    // Detach the shared memory segment from the process's address space
    shmdt(d);  // Detach shared memory
}
