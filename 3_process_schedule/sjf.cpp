#include <iostream>
#include <climits>

using namespace std;

int main()
{
    int n;
    int arrival[100], burst[100], remaining[100];
    int complete = 0, currentTime = 0, minBurst = INT_MAX;
    int shortest = 0, finishTime;
    bool found = false;
    int waitingTime[100] = {0}, turnaroundTime[100] = {0};

    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter the arrival time and burst time of each process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << " - Arrival Time: ";
        cin >> arrival[i];
        cout << "Burst Time: ";
        cin >> burst[i];
        remaining[i] = burst[i];
    }

    while (complete != n)
    {
        found = false;
        minBurst = INT_MAX;

        // Find process with minimum remaining burst time at current time
        for (int i = 0; i < n; i++)
        {
            if (arrival[i] <= currentTime && remaining[i] > 0 && remaining[i] < minBurst)
            {
                minBurst = remaining[i];
                shortest = i;
                found = true;
            }
        }

        if (!found)
        {
            currentTime++;
            continue;
        }

        // Process the selected process
        remaining[shortest]--;
        currentTime++;

        // If a process finishes
        if (remaining[shortest] == 0)
        {
            complete++;
            finishTime = currentTime;
            turnaroundTime[shortest] = finishTime - arrival[shortest];
            waitingTime[shortest] = turnaroundTime[shortest] - burst[shortest];
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t" << arrival[i] << "\t\t" << burst[i]
             << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }

    return 0;
}
