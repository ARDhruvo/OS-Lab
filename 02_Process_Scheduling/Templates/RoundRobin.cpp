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

void GanttChart(const vector<pair<int, int>> &gantt)
{
    cout << "\nGantt Chart:\n|";
    for (const auto &entry : gantt)
    {
        if (entry.first == -1)
            cout << " Idle |";
        else
            cout << " P" << entry.first << " |";
    }

    cout << "\n0";
    int currentTime = 0;
    for (const auto &entry : gantt)
    {
        currentTime += entry.second;
        cout << "    " << currentTime;
    }
    cout << "\n";
}

void RoundRobin(vector<process> &p, int timeQuantum)
{
    int n = p.size();
    vector<int> remainingBT(n);
    for (int i = 0; i < n; i++)
        remainingBT[i] = p[i].cT;

    int currentTime = 0;
    bool done;
    vector<pair<int, int>> gantt; // pair<pid, execution_time>

    do
    {
        done = true;
        for (int i = 0; i < n; i++)
        {
            if (remainingBT[i] > 0 && p[i].aT <= currentTime)
            {
                done = false;
                int execTime = min(timeQuantum, remainingBT[i]);
                gantt.push_back({p[i].pid, execTime});
                currentTime += execTime;
                remainingBT[i] -= execTime;

                if (remainingBT[i] == 0)
                {
                    p[i].tAT = currentTime - p[i].aT;
                    p[i].wT = p[i].tAT - p[i].cT;
                }
            }
        }

        // Check for idle time
        if (done)
        {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (remainingBT[i] > 0 && p[i].aT > currentTime)
                {
                    nextArrival = min(nextArrival, p[i].aT);
                }
            }
            if (nextArrival != INT_MAX && nextArrival > currentTime)
            {
                int idleTime = nextArrival - currentTime;
                gantt.push_back({-1, idleTime});
                currentTime = nextArrival;
                done = false;
            }
        }
    } while (!done);

    cout << "\nProcess\tArrival Time\tCPU Burst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &proc : p)
    {
        cout << proc.pid << "\t" << proc.aT << "\t\t" << proc.cT << "\t\t" << proc.wT << "\t\t" << proc.tAT << "\n";
    }

    GanttChart(gantt);
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

    int timeQuantum;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    RoundRobin(p, timeQuantum);

    return 0;
}
