#include <stdio.h>   // Standard library for input and output functions (e.g., printf, scanf)
#include <stdlib.h>  // Standard library for functions like atoi (to convert string to integer)

// Function to perform binary search on an array
int binary(int arr[], int l, int h, int search) {
    // Loop until the low index is less than or equal to the high index
    while (l <= h) {
        // Calculate the middle index
        int mid = l + (h - l) / 2;

        // Check if the middle element is the search element
        if (arr[mid] == search) {
            return mid;  // Return the index if the element is found
        }
        // If the search element is greater, ignore the left half
        else if (search > arr[mid]) {
            l = mid + 1;
        }
        // If the search element is smaller, ignore the right half
        else {
            h = mid - 1;
        }
    }
    return -1;  // Return -1 if the element is not found
}

// Main function to handle input and call the binary search function
void main(int argc, char *argv[]) {
    int arr[argc - 1], key;  // Declare an array and a variable for the key

    // Loop to convert command-line arguments to integers and store them in the array
    for (int i = 1; i < argc; i++) {
        arr[i - 1] = atoi(argv[i]);  // Convert and assign each argument (skip the program name)
    }

    // Print the size of the array
    printf("Size Of Array: %d\n", argc - 1);

    // Print the elements of the array
    printf("Elements are: \n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%d\t", arr[i]);  // Print each element followed by a tab
    }

    // Prompt the user to enter the search element
    printf("\nEnter the Search Element: ");
    scanf("%d", &key);  // Read the key from the user

    // Call the binary search function and store the result
    int result = binary(arr, 0, argc - 2, key);  // Use argc - 2 for the correct upper bound

    // Print the result based on whether the element was found
    if (result == -1) {
        printf("\nElement not found\n");
    } else {
        printf("\nElement found at index: %d\n", result);
    }
}
