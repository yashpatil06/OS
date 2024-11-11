#include <stdio.h>      // Standard I/O library for input/output operations
#include <string.h>     // String manipulation functions
#include <fcntl.h>      // File control options (e.g., open())
#include <sys/types.h>  // Data type definitions for system calls
#include <sys/stat.h>   // Definitions for file modes and permissions
#include <unistd.h>     // Standard symbolic constants and types (e.g., close())

// Main function
int main() {
    char *fifo1 = "fifo1";         // Name of the FIFO for reading input
    char *fifo2 = "fifo2";         // Name of the FIFO for sending output
    char buffer1[100];             // Buffer to store the data read from fifo1
    int d1, d2;                    // File descriptors for FIFO1 and FIFO2
    int i = 0;                     // Index for iterating through the buffer
    int cc = 0;                    // Character count (excluding spaces and newlines)
    int ln = 0;                    // Line count
    int wc = 0;                    // Word count

    // Open fifo1 for reading
    d1 = open(fifo1, O_RDONLY);
    
    // Read data from fifo1 into buffer1
    read(d1, buffer1, sizeof(buffer1));
    
    // Iterate through buffer1 to count characters, words, and lines
    while (buffer1[i] != '#' && buffer1[i] != '\0') {  // Continue until '#' or end of string
        if (buffer1[i] == ' ') {                       // Check for a space character
            wc++;                                      // Increment word count
        } else if (buffer1[i] == '\n') {               // Check for a newline character
            ln++;                                      // Increment line count
            wc++;                                      // Increment word count for the line break
        } else {                                       // Any other character
            cc++;                                      // Increment character count
        }
        i++;                                           // Move to the next character in the buffer
    }

    // Open a file named "Shubham.txt" for writing results
    FILE *fp = fopen("memory.txt", "w");
    if (fp == NULL) {                                  // Check if the file was opened successfully
        perror("Error opening file");                  // Print an error message if file opening failed
        return 1;                                      // Return error code
    }

    // Write the counts to the file
    fprintf(fp, "\nLine count = %d", ln);              // Write the line count
    fprintf(fp, "\nWord count = %d", wc);              // Write the word count
    fprintf(fp, "\nCharacter count = %d", cc);         // Write the character count

    // Close the file after writing
    fclose(fp);

    // Create fifo2 with read/write permissions
    mkfifo(fifo2, 0666);
    
    // Open fifo2 for writing
    d2 = open(fifo2, O_WRONLY);
    
    // Write the filename "memory.txt" to fifo2
    write(d2, "memory.txt", 11);
    
    // Close fifo2 after writing
    close(d2);

    return 0;  // Return with success status
}
