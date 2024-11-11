#include <stdio.h>  // Include standard I/O library for input/output functions

int main() {
    int numProcesses, numResources;

    // Prompt the user to enter the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);  // Read the number of processes
    
    // Prompt the user to enter the number of resources
    printf("Enter number of resources: ");
    scanf("%d", &numResources);  // Read the number of resources

    // Declare matrices for allocation and maximum resource requirements
    int allocationMatrix[numProcesses][numResources];
    int maxMatrix[numProcesses][numResources];
    
    // Declare an array for available resources
    int available[numResources];

    // Prompt the user to enter the allocation matrix
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            scanf("%d", &allocationMatrix[i][j]);  // Read allocation matrix values

    // Prompt the user to enter the maximum matrix
    printf("Enter Max Matrix:\n");
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            scanf("%d", &maxMatrix[i][j]);  // Read maximum matrix values

    // Prompt the user to enter the available resources
    printf("Enter Available Resources:\n");
    for (int j = 0; j < numResources; j++)
        scanf("%d", &available[j]);  // Read available resources

    // Initialize arrays for finished status and safe sequence
    int isFinished[numProcesses], safeSequence[numProcesses], index = 0;
    
    // Mark all processes as not finished initially
    for (int k = 0; k < numProcesses; k++) {
        isFinished[k] = 0;  // Initialize `isFinished` array to 0 (false)
    }

    // Declare and calculate the need matrix
    int needMatrix[numProcesses][numResources];
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++)
            needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];  // Calculate need matrix
    }

    // Implementing Banker's algorithm to find the safe sequence
    for (int k = 0; k < numProcesses; k++) {
        for (int i = 0; i < numProcesses; i++) {
            if (isFinished[i] == 0) {  // Check if the process is not yet finished
                int flag = 0;  // A flag to indicate if the resources can be allocated
                
                // Check if the process's need can be satisfied with the available resources
                for (int j = 0; j < numResources; j++) {
                    if (needMatrix[i][j] > available[j]) {  // If need exceeds available
                        flag = 1;  // Set flag to indicate that allocation is not possible
                        break;  // Exit the loop as resources can't be allocated to this process
                    }
                }

                // If the resources can be allocated (flag remains 0)
                if (flag == 0) {
                    safeSequence[index++] = i;  // Add process to the safe sequence
                    
                    // Release resources from the process to the available pool
                    for (int y = 0; y < numResources; y++)
                        available[y] += allocationMatrix[i][y];  // Add allocated resources back to available

                    isFinished[i] = 1;  // Mark the process as finished
                }
            }
        }
    }

    // Check if all processes are finished and a safe sequence exists
    int flag = 1;  // Assume the system is in a safe state
    for (int i = 0; i < numProcesses; i++) {
        if (isFinished[i] == 0) {  // If any process is not finished
            flag = 0;  // Set flag to indicate the system is not safe
            printf("The system is not safe.\n");  // Print unsafe message
            break;  // Exit the loop as the system is not safe
        }
    }

    // If the system is safe, print the safe sequence
    if (flag == 1) {
        printf("SAFE Sequence: ");
        for (int i = 0; i < numProcesses - 1; i++)
            printf("P%d -> ", safeSequence[i] + 1);  // Print each process in the sequence
        printf("P%d\n", safeSequence[numProcesses - 1] + 1);  // Print the last process
    }

    return 0;  // Return 0 to indicate successful execution
}
