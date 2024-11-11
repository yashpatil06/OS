#include <iostream>
using namespace std;

struct Process
{
    int arrival;
    int burst;
};

void fcfs(int n, Process p[], int wait[], int tat[])
{
    wait[0] = 0;
    tat[0] = p[0].burst;
    int avgWT, avgTAT;

    for (int i = 1; i < n; i++)
    {
        wait[i] = tat[i - 1] - p[i].arrival;
        if (wait[i] < 0)
        {
            wait[i] = 0;
        }
        tat[i] = wait[i] + p[i].burst;
    }
}

void sort(int n, Process p[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival > p[j + 1].arrival)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

float average(int n, int arr[])
{
    int sum = 0;
    float avg;

    for (int i = 0; i < n; i++)
    {
        sum = sum + arr[i];
    }
    avg = (float)sum / n;
    return avg;
}

int main()
{
    int n;
    cout << "\nEnter the number of processes:\n";
    cin >> n;

    Process p[n];
    int wait[n];
    int tat[n];

    cout << "\nEnter the process Arrival and Service time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nProcess " << i + 1 << " Arrival Time: ";
        cin >> p[i].arrival;

        cout << "Process " << i + 1 << " Service Time: ";
        cin >> p[i].burst;
    }

    sort(n, p);
    fcfs(n, p, wait, tat);

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t" << p[i].arrival << "\t\t" << p[i].burst
             << "\t\t" << wait[i] << "\t\t" << tat[i] << endl;
    }
    cout << "\nAverage TAT=" << average(n, tat);
    cout << "\nAverage WT=" << average(n, wait);
    return 0;
}
