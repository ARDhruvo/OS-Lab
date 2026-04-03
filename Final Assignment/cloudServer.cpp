#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define none -1

/*
3 3 2
7 5 3
0 1 0
3 2 2
2 0 0
9 0 2
3 0 2
2 2 2
2 1 1
0
8
1
4
2
9
3
5
*/

struct process
{
    int pid;
    int aT;
    int bT;
    int totalNeed;
    int priority = none;
    int cT;
    int wT;
    int tAT;
};

void printNeedMatrix(vector<vector<int>> need, vector<process> processes)
{
    cout << "Need Matrix:" << endl;
    for (int i = 0; i < need.size(); i++)
    {
        cout << "P" << i << ": [";
        for (int j = 0; j < need[i].size() - 2; j++)
        {
            cout << need[i][j] << ", ";
        }
        cout << need[i][need[i].size() - 2] << "] \t Total Need: " << processes[i].totalNeed << endl;
    }
}

queue<int> Banker(vector<process> processes, vector<vector<int>> allocation, vector<vector<int>> need, vector<int> available, vector<vector<int>> max)
{
    queue<int> safeSequence;
    vector<bool> assigned(need.size(), false);
    int run = processes.size() - 1;

    for (int i = 0; i < run; i++)
    {
        int selected = 4;
        int selectedNeed = 0;
        int assignedNeed = 0;

        for (int j = 0; j < processes.size() - 1; j++)
        {
            if (!assigned[j])
            {
                if (available[0] >= need[j][0] && available[1] >= need[j][1] && available[2] >= need[j][2])
                {
                    selectedNeed = need[j][0] + need[j][1] + need[j][2];
                    if (selectedNeed > assignedNeed)
                    {
                        assignedNeed = selectedNeed;
                        selected = j;
                    }
                }
            }
        }

        if (selected == 4)
        {
            queue<int> failedSequence;
            return failedSequence; // Return empty queue
        }
        else
        {
            safeSequence.push(processes[selected].pid);
            assigned[selected] = true;

            for (int j = 0; j < available.size(); j++)
            {
                available[j] += allocation[selected][j];
            }
        }
    }

    return safeSequence;
}

bool safety(vector<process> processes, vector<vector<int>> allocation, vector<vector<int>> need, vector<int> available, vector<vector<int>> max)
{
    // Implementation of the safety algorithm
    queue<int> state = Banker(processes, allocation, need, available, max);
    paragraph;
    if (state.empty())
    {
        cout << "DEADLOCK RISK --- System Halted" << endl;
        return false;
    }
    else
    {
        cout << "Result: SAFE STATE\nSafe Sequence: " << endl;
        cout << "P" << state.front() << " ";
        state.pop();
        while (!state.empty())
        {
            cout << "-> P" << state.front() << " ";
            state.pop();
        }
        cout << endl;
        return true;
    }
}

struct ComparePriority
{
    bool operator()(const process &a, const process &b)
    {
        if (a.priority == b.priority)
            return a.aT > b.aT;         // earlier arrival has higher priority
        return a.priority > b.priority; // smaller priority number → higher priority
    }
};

vector<int> PriorityScheduling(vector<process> &processes, int n)
{
    vector<int> completionIndex(n, none);
    vector<process> sorted = processes;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (sorted[j].aT > sorted[j + 1].aT)
            {
                swap(sorted[j], sorted[j + 1]);
            }
        }
    }

    vector<int> remBT(n);
    for (int i = 0; i < n; i++)
    {
        remBT[i] = sorted[i].bT;
    }

    priority_queue<process, vector<process>, ComparePriority> readyQueue;

    int time = 0;
    int idx = 0;
    int completed = 0;
    int lastPrintedPid = -1;

    vector<int> timeStamps;
    bool first = true;

    while (completed < n)
    {
        while (idx < n && sorted[idx].aT <= time)
        {
            readyQueue.push(sorted[idx]);
            idx++;
        }

        if (readyQueue.empty())
        {
            if (idx < n)
            {
                time = sorted[idx].aT;
                continue;
            }
            else
            {
                break;
            }
        }
        process current = readyQueue.top();
        readyQueue.pop();
        int pidIdx = -1;
        for (int i = 0; i < n; i++)
        {
            if (sorted[i].pid == current.pid)
            {
                pidIdx = i;
                break;
            }
        }

        if (lastPrintedPid != current.pid)
        {
            if (first)
            {
                cout << "| \tP" << current.pid << "\t |";
                first = false;
            }
            else
            {
                cout << " \tP" << current.pid << " \t |";
            }
            timeStamps.push_back(time);
            lastPrintedPid = current.pid;
        }

        int nextArrival = (idx < n) ? sorted[idx].aT : INT_MAX;

        int timeToFinish = remBT[pidIdx];
        int timeToNextArrival = nextArrival - time;

        if (timeToNextArrival < timeToFinish)
        {
            remBT[pidIdx] -= timeToNextArrival;
            time = nextArrival;
            process preempted = current;
            readyQueue.push(preempted);
        }
        else
        {
            time += remBT[pidIdx];
            remBT[pidIdx] = 0;
            completionIndex[completed] = pidIdx;
            completed++;
        }
    }

    timeStamps.push_back(time);
    paragraph;
    for (auto i : timeStamps)
    {
        cout << i << "\t\t";
    }
    paragraph;

    return completionIndex;
}

vector<int> scheduling(vector<process> &processes, int n)
{
    cout << "--- Priority Scheduling ---" << endl;
    return PriorityScheduling(processes, n);
}

void LRU(int page, vector<int> &frames, map<int, int> &pageTable, vector<int> &refStr, int i)
{
    bool replaced = false; // For checking if any frame is empty
    for (int f = 0; f < frames.size(); f++)
    {
        if (frames[f] == none)
        {
            frames[f] = page; // Placing the new page in the empty frame
            replaced = true;
            break;
        }
    }

    if (!replaced)
    {
        int lruPage = frames[0];
        int lruIndex = 0;
        for (int f = 0; f < frames.size(); f++)
        {
            if (pageTable[frames[f]] < pageTable[lruPage])
            {
                lruPage = frames[f]; // This ensures O(F) search
                lruIndex = f;
                /*
                 * The main idea is that by using a previously hashed map
                 * we only need to check the hash map of the pages in the frame
                 * Since searching through the frames is O(F) and accessing the last used index of a page is O(1)
                 * The overall time complexity of finding the LRU page is O(F)
                 */
            }
        }
        frames[lruIndex] = page;
    }
}

int pageReplacement(vector<int> &frames, map<int, int> &pageTable, vector<int> &refStr)
{

    int pageFaultCount = 0;
    for (int i = 0; i < refStr.size(); i++)
    {
        int page = refStr[i];
        pageTable[page] = i; // Updating the last used index of the page for O(F) access

        bool pageFault = true; // Assuming page fault until we find the page in the frames

        for (int i = 0; i < frames.size(); i++)
        {
            if (frames[i] == page)
            {
                pageFault = false; // Page Hit; The page is already loaded in the frames
                break;
            }
        }

        if (pageFault)
        {
            pageFaultCount++;
            LRU(page, frames, pageTable, refStr, i);
            // pageFaults(i, frames, refStr, pageFaultCount);
        }
    }
    return pageFaultCount;
}

int main()
{
    // Input

    int n = 4; // As mentioned in the assignment; p0 -> p3, p4 is for future calculation
    int resourceType = 3;
    vector<process> processes(n + 1);

    vector<vector<int>> allocation(n + 1, vector<int>(n, 0));
    vector<vector<int>> max(n, vector<int>(n, 0));
    vector<vector<int>> need(n, vector<int>(n, 0));

    vector<int> available(resourceType, 0);

    cout << "Enter Available resources [CPU MEM IO]: ";
    for (int i = 0; i < resourceType; i++)
    {
        // cout << "Taking resource no. " << i << endl;
        cin >> available[i];
        // cout << "Resource " << i << " = " << available[i] << endl;
    }

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i;

        cout << "Enter Max demand for P" << i << ": " << endl;
        for (int j = 0; j < resourceType; j++)
        {
            cin >> max[i][j];
        }

        cout << "Enter Allocation for P" << i << ": " << endl;
        for (int j = 0; j < resourceType; j++)
        {
            cin >> allocation[i][j];

            need[i][j] = max[i][j] - allocation[i][j];

            processes[i].totalNeed += need[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time for P" << i << ": ";
        cin >> processes[i].aT;
        cout << "Enter Burst Time for P" << i << ": ";
        cin >> processes[i].bT;
    }

    int priorityCount = 1;
    for (int i = 0; i < n; i++)
    {
        int highest = n;
        for (int j = 0; j < n; j++)
        {
            if (processes[j].priority == none)
            {
                highest = j;
                break;
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (processes[j].priority == none)
            {
                if (processes[j].totalNeed > processes[highest].totalNeed)
                {
                    highest = j;
                }
            }
        }
        processes[highest].priority = priorityCount++;
    }
    paragraph;

    cout << "--- Banker's Algorithm ---" << endl;
    paragraph;

    printNeedMatrix(need, processes);

    paragraph;

    bool safe = safety(processes, allocation, need, available, max);
    if (safe)
    {
        cout << "Proceeding to Scheduling..." << endl;
        paragraph;

        vector<int> scheduledProcesses = scheduling(processes, n);
        // pageReplacement(scheduledProcesses);
    }

    return 0;
}
