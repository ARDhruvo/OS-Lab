#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int aT;
    int cT;
    int wT;
    int tAT;
};

void GanttChart(const vector<process> &p)
{
    cout << "\nGantt Chart:\n|";
    int currentTime = 0;
    for (const auto &proc : p)
    {
        if (currentTime < proc.aT)
        {
            cout << " Idle |";
            currentTime = proc.aT;
        }
        cout << " P" << proc.pid << " |";
        currentTime += proc.cT;
    }
    cout << "\n0";
    currentTime = 0;
    for (const auto &proc : p)
    {
        if (currentTime < proc.aT)
        {
            currentTime = proc.aT;
            cout << "    " << currentTime;
        }
        currentTime += proc.cT;
        cout << "    " << currentTime;
    }
    cout << "\n";
}

void FCFS_Scheduling(vector<process> &p)
{
    int n = p.size();
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < p[i].aT)
            currentTime = p[i].aT; // CPU is idle until the process arrives
        currentTime += p[i].cT;
        p[i].tAT = currentTime - p[i].aT;
        p[i].wT = p[i].tAT - p[i].cT;
    }

    // double totalWT = 0, totalTAT = 0;
    cout << "\nProcess\tArrival Time\tCPU Burst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &proc : p)
    {
        cout << proc.pid << "\t" << proc.aT << "\t\t" << proc.cT << "\t\t" << proc.wT << "\t\t" << proc.tAT << "\n";
        // totalWT += proc.wT;
        // totalTAT += proc.tAT;
    }

    // cout << fixed << setprecision(2);
    // cout << "\nAverage Waiting Time: " << (totalWT / n);
    // cout << "\nAverage Turnaround Time: " << (totalTAT / n) << "\n";

    GanttChart(p);
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<process> p(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and CPU burst time for process " << i + 1 << ": ";
        cin >> p[i].aT >> p[i].cT;
        p[i].pid = i + 1;
    }

    // Sort processes by arrival time
    sort(p.begin(), p.end(), [](const process &a, const process &b)
         { return a.aT < b.aT; });

    FCFS_Scheduling(p);
    return 0;
}