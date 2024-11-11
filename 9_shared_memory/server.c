#include <stdio.h>       // Standard I/O library for input/output functions
#include <stdlib.h>      // Standard library for system functions like system()
#include <sys/ipc.h>     // Header for IPC (Inter-Process Communication) mechanisms
#include <sys/shm.h>     // Header for shared memory functions

// Structure to hold data in shared memory
struct data {
    char s[100];  // Character array to store a string (the data to be shared)
    int flag;     // Integer flag used for signaling between processes
};

void main() {
    // Generate a unique key for shared memory using ftok()
    key_t key = ftok("memory.txt", 'A');  // Create an IPC key based on "memory.txt" and a character 'A'

    // Create or access a shared memory segment of size 1024 bytes with read/write permissions
    int shmid = shmget(key, 1024, 0777 | IPC_CREAT);  // Create shared memory segment with key and permissions

    // Attach the shared memory segment to the process's address space
    struct data *d = shmat(shmid, NULL, 0);  // Attach shared memory to pointer `d`

    // Initialize the flag in the shared memory structure to 0 (indicating data is not yet ready)
    d->flag = 0;

    // Prompt the user to enter the data to be sent
    printf("\nEnter the data to be sent: ");
    gets(d->s);  // Read a string from standard input and store it in `d->s`

    // Set the flag to 1 to indicate that data is ready for reading
    d->flag = 1;

    // Wait until the flag is set to -1 (indicating data has been read)
    while (d->flag != -1) {
        printf("\nWaiting...");  // Print "Waiting..." to indicate waiting status
        sleep(2);                // Pause for 2 seconds before checking the flag again
    }

    // Display current shared memory segments using the `ipcs -m` system command
    system("ipcs -m");

    // Detach the shared memory segment from the process's address space
    shmdt(d);  // Detach shared memory

    // Mark the shared memory segment for deletion
    shmctl(shmid, IPC_RMID, NULL);  // Remove the shared memory segment

    // Display updated shared memory segments
    system("ipcs -m");
}


// 2 terminal
//1 gcc server.c -o a.out      2 gcc clint.c -o b.out
// 3./a.out                    4 ./b.out