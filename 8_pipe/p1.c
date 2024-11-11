#include <stdio.h>      // Standard I/O library for input/output operations
#include <string.h>     // String manipulation functions
#include <fcntl.h>      // File control options for opening files
#include <sys/types.h>  // Data type definitions used in system calls
#include <sys/stat.h>   // Definitions for file modes used in system calls
#include <unistd.h>     // UNIX standard function definitions (e.g., sleep, read, write)

// Main function
int main() {
    char *fifo1 = "fifo1"; // Name of the first FIFO for sending data
    char *fifo2 = "fifo2"; // Name of the second FIFO for receiving data
    char ch, buffer[100];  // Character for reading input, buffer for storing user input
    int d1, i = 0;         // File descriptor for FIFO1 and index for buffer
    
    // Create the FIFO1 with read/write permissions (0666)
    mkfifo(fifo1, 0666); 
    
    // Open FIFO1 in write-only mode
    d1 = open(fifo1, O_WRONLY);
    
    // Prompt the user for input
    printf("\nEnter data (end with #): ");
    ch = getchar(); // Read a character from the standard input
    
    // Loop until the user enters '#'
    while (ch != '#') {
        buffer[i] = ch; // Store the character in the buffer
        i++;            // Increment the index
        ch = getchar(); // Read the next character
    }
    
    // End the buffer with '#'
    buffer[i] = '#';
    
    // Write the buffer contents to FIFO1
    write(d1, buffer, sizeof(buffer));
    
    // Close FIFO1 after writing
    close(d1);
    
    // Sleep for 2 seconds (simulating a delay)
    sleep(2);
    
    // Open FIFO2 in read-only mode to read the filename
    int d2 = open(fifo2, O_RDONLY);
    char buffer2[100]; // Buffer for storing the filename
    
    // Read data from FIFO2 into buffer2
    read(d2, buffer2, sizeof(buffer2));
    
    // Print the filename received from the second FIFO
    printf("User2: %s\n", buffer2);
    
    // Close FIFO2 after reading
    close(d2);
    
    // Open the file received from User2
    FILE *fptr = fopen(buffer2, "r");
    
    // Check if the file pointer is NULL (indicating an error)
    if (fptr == NULL) {
        perror("Error opening file"); // Print error message
        return 1; // Return with an error status
    }
    
    // Read and print the file contents character by character until EOF
    while ((ch = fgetc(fptr)) != EOF) {
        printf("%c", ch);
    }
    
    // Close the file after reading
    fclose(fptr);
    
    return 0; // Return with success status
}


//2 terminal
//compile both p1.c -o a.out  p2.c -0 a.out
