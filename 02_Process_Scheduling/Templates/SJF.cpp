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

void SJF_Scheduling(vector<process> &p)
{
    int n = p.size();
    int completed = 0, currentTime = 0;
    vector<bool> isCompleted(n, false);

    while (completed < n)
    {
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].aT <= currentTime && !isCompleted[i])
            {
                if (p[i].cT < minBurst)
                {
                    minBurst = p[i].cT;
                    idx = i;
                }
                else if (p[i].cT == minBurst)
                {
                    if (p[i].aT < p[idx].aT)
                    {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            currentTime += p[idx].cT;
            p[idx].tAT = currentTime - p[idx].aT;
            p[idx].wT = p[idx].tAT - p[idx].cT;
            isCompleted[idx] = true;
            completed++;
        }
        else
        {
            currentTime++;
        }
    }

    cout << "\nProcess\tArrival Time\tCPU Burst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &proc : p)
    {
        cout << proc.pid << "\t" << proc.aT << "\t\t" << proc.cT << "\t\t" << proc.wT << "\t\t" << proc.tAT << "\n";
    }

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

    sort(p.begin(), p.end(), [](const process &a, const process &b)
         {
        if (a.aT == b.aT)
            return a.cT < b.cT;
        return a.aT < b.aT; });

    SJF_Scheduling(p);

    return 0;
}