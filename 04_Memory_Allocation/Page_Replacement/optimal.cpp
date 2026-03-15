#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define empty -1
#define inf refStr.size() + 1

/*
3
22
7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
 */

void refStrPrint(vector<int> &refStr)
{
    cout << "Reference string: ";
    for (int page : refStr)
    {
        cout << page << " ";
    }
    paragraph;
}

void displayFrames(vector<int> &frames)
{
    cout << "Current frames: ";
    for (int page : frames)
    {
        if (page != empty) // For non empty frame
        {
            cout << page << " ";
        }
        else // For empty frame
        {
            cout << "- ";
        }
    }
    paragraph;
}

void pageFaults(int index, vector<int> &frames, vector<int> &refStr, int count)
{
    cout << "Page fault no.: " << count << endl;
    cout << "Page fault at position " << index << endl;
    for (int i = 0; i <= index; i++)
    {
        cout << refStr[i] << " ";
    }
    paragraph;
    displayFrames(frames);
    paragraph;
}

map<int, int> optUpdate(map<int, int> &pageTable, vector<int> &refStr, int i)
{
    for (int j = 0; j >= i; j++)
    {
        pageTable[refStr[j]] = j; // Updating the last used index of the page for O(F) access
    }
    return pageTable;
}

int optSearch(int page, vector<int> &refStr, int i)
{
    int optIndex = inf;
    for (int j = i; j < refStr.size(); j++)
    {
        if (refStr[j] == page)
        {
            optIndex = j;
            break;
        }
    }
    return optIndex;
}

void Optimal(int page, vector<int> &frames, vector<int> &refStr, int currentIndex)
{
    // 1. If there is an empty frame, use it
    for (int f = 0; f < frames.size(); f++)
    {
        if (frames[f] == empty)
        {
            frames[f] = page;
            return;
        }
    }

    // 2. No empty frame → find victim
    int victim = 0;    // frame index to replace
    int farthest = -1; // largest next use seen so far

    for (int f = 0; f < frames.size(); f++)
    {
        // Look for the next occurrence of frames[f] after currentIndex
        int nextUse = optSearch(frames[f], refStr, currentIndex + 1);
        if (nextUse > farthest)
        { // we want the largest
            farthest = nextUse;
            victim = f;
        }
    }

    frames[victim] = page;
}

int pageReplacement(vector<int> &frames, vector<int> &refStr)
{

    int pageFaultCount = 0;
    for (int i = 0; i < refStr.size(); i++)
    {
        int page = refStr[i];
        // lruPageTable[page] = i; // Updating the last used index of the page for O(F) access
        // optPageTable[page] = i; // Updating the last used index of the page for O(F) access

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
            // LRU(page, frames, lruPageTable, refStr, i);
            // FIFO(page, frames, pageFaultCount, refStr, i);
            Optimal(page, frames, refStr, i);

            pageFaultCount++;
            pageFaults(i, frames, refStr, pageFaultCount);
        }
    }
    return pageFaultCount;
}

int main()
{
    int frameSize, refStrSize;
    cout << "Enter the number of frames: ";
    cin >> frameSize;
    cout << "Enter the size of the reference string: ";
    cin >> refStrSize;
    map<int, int> lruPageTable;           // <page number, last used index> for keeping track of page usage
    map<int, int> optPageTable;           // <page number, last used index> for keeping track of page usage
    vector<int> frames(frameSize, empty); // Frames are always empty at the start
    vector<int> refStr(refStrSize);
    cout << "Enter the reference string (space separated): ";
    for (int i = 0; i < refStrSize; i++)
    {
        cin >> refStr[i];
        lruPageTable[refStr[i]] = empty; // Initializing all pages as not used
        optPageTable[refStr[i]] = inf;   // Initializing all pages as not used
    }
    paragraph;

    // Initial Condition:
    refStrPrint(refStr);
    paragraph;
    displayFrames(frames);
    paragraph;

    // Main Simulation:
    int pageFaultCount = pageReplacement(frames, refStr);
    paragraph;

    cout << "Final Output: " << endl;
    cout << "Total page hits: " << refStrSize - pageFaultCount << endl;
    cout << "Total page faults: " << pageFaultCount << endl;
    displayFrames(frames);

    return 0;
}
