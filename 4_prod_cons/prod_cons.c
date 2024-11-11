#include <stdio.h>    // Standard library for input and output
#include <stdlib.h>   // Standard library for functions like rand
#include <semaphore.h> // Library for semaphores
#include <pthread.h>   // Library for POSIX threads
#include <unistd.h>    // Library for sleep function

// Declaration of semaphores
sem_t e, f, s;

// Shared buffer and pointers for producer and consumer
int data[5], in = 0, out = 0;

// Producer function to produce data
void *producer(void *arg) {
    // Wait for empty slot and mutual exclusion
    sem_wait(&e);      // Decrement `e` semaphore to check if space is available
    sem_wait(&s);      // Decrement `s` semaphore for mutual exclusion

    // Critical section: produce data
    data[in] = rand(); // Generate random data and place it in the buffer
    printf("\nProducer generated: %d", data[in]);
    in = (in + 1) % 5; // Move `in` pointer cyclically in the buffer

    // Signal mutual exclusion and increment `f` to indicate produced data
    sem_post(&s);      // Increment `s` to release mutual exclusion
    sem_post(&f);      // Increment `f` to signal data is available
}

// Consumer function to consume data
void *consumer(void *arg) {
    int value; // Variable to hold the consumed value

    do {
        // Wait for full slot and mutual exclusion
        sem_wait(&f);  // Decrement `f` semaphore to check if data is available
        sem_wait(&s);  // Decrement `s` for mutual exclusion

        // Critical section: consume data
        value = data[out]; // Read data from the buffer
        printf("\nConsumer read: %d", value);
        out = (out + 1) % 5; // Move `out` pointer cyclically in the buffer

        // Signal mutual exclusion and increment `e` to indicate empty space
        sem_post(&s);      // Increment `s` to release mutual exclusion
        sem_post(&e);      // Increment `e` to signal space is available

        // Check the value of `e` to stop when the buffer is full
        sem_getvalue(&e, &value);
    } while (value != 5); // Continue until the buffer is full (all slots empty)
}

// Main function to create and join threads
void main() {
    pthread_t p[8], c; // Array for producer threads and a single consumer thread
    int i;             // Loop counter

    // Initialize semaphores: `f` to 0 (full slots), `e` to 5 (empty slots), and `s` to 1 (binary semaphore for mutual exclusion)
    sem_init(&f, 0, 0);
    sem_init(&e, 0, 5);
    sem_init(&s, 0, 1);

    // Create a consumer thread
    pthread_create(&c, NULL, consumer, NULL);

    // Create 8 producer threads
    for (i = 0; i < 8; ++i) {
        pthread_create(&p[i], NULL, producer, NULL);
    }

    // Allow threads time to run
    sleep(2);
}
