#include <stdlib.h>    // Standard library for general utilities
#include <stdio.h>     // Standard library for input and output
#include <unistd.h>    // Library for Unix standard functions
#include <semaphore.h> // Library for semaphore functions
#include <pthread.h>   // Library for POSIX threads

// Declare semaphores for reader and writer control
sem_t r, w;

// Shared variable to keep track of the number of readers
int count = 0;

// Reader function to simulate reading
void *Reader(void *arg) {
    // Wait on the reader semaphore to enter critical section
    sem_wait(&r); // Decrease `r` to ensure mutual exclusion when accessing `count`
    count++; // Increment the number of readers
    
    // If the first reader is entering, lock the writer semaphore
    if (count == 1) {
        sem_wait(&w); // Prevent writers from writing while readers are present
    }
    // Signal the reader semaphore to allow other readers to proceed
    sem_post(&r);

    // Critical section where the reader reads
    printf("\nReader is reading");

    // Wait on the reader semaphore before decrementing `count`
    sem_wait(&r);
    count--; // Decrement the number of readers

    // If the last reader is leaving, release the writer semaphore
    if (count == 0) {
        sem_post(&w); // Allow writers to proceed
    }
    // Signal the reader semaphore to allow other readers to proceed
    sem_post(&r);
}

// Writer function to simulate writing
void *Writer(void *arg) {
    // Wait on the writer semaphore to gain exclusive access to the resource
    sem_wait(&w);
    
    // Critical section where the writer writes
    printf("\nWriter is writing");
    
    // Signal the writer semaphore to allow others (readers or writers) to proceed
    sem_post(&w);
}

int main() {
    // Arrays to hold reader and writer threads
    pthread_t reader[3], writer[3];

    // Initialize semaphores for readers and writers
    sem_init(&r, 0, 1); // Initialize `r` as a binary semaphore (used for mutual exclusion)
    sem_init(&w, 0, 1); // Initialize `w` as a binary semaphore (used for writer access control)

    // Create 3 reader threads and 3 writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&reader[i], NULL, Reader, NULL); // Create a reader thread
        pthread_create(&writer[i], NULL, Writer, NULL); // Create a writer thread
    }

    // Join all the reader and writer threads
    for (int i = 0; i < 3; i++) {
        pthread_join(reader[i], NULL); // Wait for the reader thread to finish
        pthread_join(writer[i], NULL); // Wait for the writer thread to finish
    }

    return 0; // Return success status
}
