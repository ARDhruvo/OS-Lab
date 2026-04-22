#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define none -1
#define inf processes.size()

/*
5
10
50 200 70 115 15
100 10 35 15 23 6 25 55 88 40
*/

void fragPrint(vector<int> &fragError)
{
    cout << "Processes that cannot be allocated due to fragmentation:" << endl;
    for (int i = 0; i < fragError.size(); i++)
    {
        cout << "Process size: " << fragError[i] << endl;
    }
}

void allocPrint(vector<int> &processes, vector<int> &allocation)
{
    cout << "Process No.\tProcess Size\tBlock No." << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        cout << i + 1 << "\t\t" << processes[i] << "\t\t";
        if (allocation[i] != none)
        {
            cout << allocation[i] + 1 << endl;
        }
        else
        {
            cout << "Not Allocated" << endl;
        }
    }
}

void blockPrint(vector<int> &partitions, vector<int> &allocation, vector<int> &processes)
{
    cout << "Block No.\tBlock Size Remaining\tProcesses" << endl;
    for (int i = 0; i < partitions.size(); i++)
    {
        cout << i + 1 << "\t\t" << partitions[i] << "\t\t\t";
        bool assigned = false;
        for (int j = 0; j < allocation.size(); j++)
        {
            if (allocation[j] == i)
            {
                cout << processes[j] << "(P" << j + 1 << ") ";
                assigned = true;
            }
        }
        if (!assigned)
        {
            cout << "None";
        }
        paragraph;
    }
}

void firstFit(vector<int> &partitions, vector<int> &processes, vector<int> &allocation, vector<int> &fragError)
{
    for (int i = 0; i < processes.size(); i++)
    {
        bool assigned = false;
        for (int j = 0; j < partitions.size(); j++)
        {
            if (partitions[j] >= processes[i])
            {
                allocation[i] = j;
                partitions[j] -= processes[i];
                assigned = true;
                break;
            }
        }
        if (!assigned)
        {
            cout << "Process " << i + 1 << " cannot be allocated." << endl;
            fragError.push_back(processes[i]);
            /*
            blockPrint(partitions, allocation, processes);
            return;
            */
        }
    }

    if (!fragError.empty())
    {
        fragPrint(fragError);
    }

    // allocPrint(processes, allocation);
    blockPrint(partitions, allocation, processes);
}

void bestFit(vector<int> &partitions, vector<int> &processes, vector<int> &allocation, vector<int> &fragError)
{
    for (int i = 0; i < processes.size(); i++)
    {
        int best = inf;
        for (int j = 0; j < partitions.size(); j++)
        {
            if (partitions[j] >= processes[i])
            {
                if (best == inf || partitions[j] < partitions[best])
                {
                    best = j;
                }
            }
        }
        if (best != inf)
        {
            allocation[i] = best;
            partitions[best] -= processes[i];
        }
        else
        {
            cout << "Process " << i + 1 << " cannot be allocated." << endl;
            fragError.push_back(processes[i]);
            /*
            blockPrint(partitions, allocation, processes);
            return;
            */
        }
    }

    if (!fragError.empty())
    {
        fragPrint(fragError);
    }

    // allocPrint(processes, allocation);
    blockPrint(partitions, allocation, processes);
}

void worstFit(vector<int> &partitions, vector<int> &processes, vector<int> &allocation, vector<int> &fragError)
{
    for (int i = 0; i < processes.size(); i++)
    {
        int worst = inf;
        for (int j = 0; j < partitions.size(); j++)
        {
            if (partitions[j] >= processes[i])
            {
                if (worst == inf || partitions[j] > partitions[worst])
                {
                    worst = j;
                }
            }
        }
        if (worst != inf)
        {
            allocation[i] = worst;
            partitions[worst] -= processes[i];
        }
        else
        {
            cout << "Process " << i + 1 << " cannot be allocated." << endl;
            fragError.push_back(processes[i]);
            /*
            blockPrint(partitions, allocation, processes);
            return;
            */
        }
    }

    if (!fragError.empty())
    {
        fragPrint(fragError);
    }

    // allocPrint(processes, allocation);
    blockPrint(partitions, allocation, processes);
}

int main()
{
    int blockNo, procNo;
    cout << "Enter the number of blocks: ";
    cin >> blockNo;
    cout << "Enter the number of processes: ";
    cin >> procNo;
    vector<int> partitions(blockNo);
    vector<int> processes(procNo);
    vector<int> allocation(procNo, none);
    vector<int> fragError;
    cout << "Enter the size of blocks: ";
    for (int i = 0; i < blockNo; i++)
    {
        cin >> partitions[i];
    }
    cout << "Enter the size of processes: ";
    for (int i = 0; i < procNo; i++)
    {
        cin >> processes[i];
    }
    paragraph;

    // firstFit(partitions, processes, allocation, fragError);
    // bestFit(partitions, processes, allocation, fragError);
    worstFit(partitions, processes, allocation, fragError);
    return 0;
}
