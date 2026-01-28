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

void SRTN_Scheduling(vector<process> &p)
{
    int n = p.size();
    int completed = 0, currentTime = 0;
    vector<int> remainingBT(n);
    for (int i = 0; i < n; i++)
        remainingBT[i] = p[i].cT;

    while (completed < n)
    {
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].aT <= currentTime && remainingBT[i] > 0)
            {
                if (remainingBT[i] < minBurst)
                {
                    minBurst = remainingBT[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            remainingBT[idx]--;
            currentTime++;

            if (remainingBT[idx] == 0)
            {
                completed++;
                p[idx].tAT = currentTime - p[idx].aT;
                p[idx].wT = p[idx].tAT - p[idx].cT;
            }
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

    // GanttChart(p);
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

    SRTN_Scheduling(p);

    return 0;
}
