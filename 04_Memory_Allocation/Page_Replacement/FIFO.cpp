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

void FIFO(int page, vector<int> &frames, int pageFaultCount)
{
    int index = pageFaultCount % frames.size();

    frames[index] = page;
}

int pageReplacement(vector<int> &frames, map<int, int> &lruPageTable, vector<int> &refStr)
{

    int pageFaultCount = 0;
    for (int i = 0; i < refStr.size(); i++)
    {
        int page = refStr[i];
        lruPageTable[page] = i; // Updating the last used index of the page for O(F) access

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
            FIFO(page, frames, pageFaultCount);

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
    vector<int> frames(frameSize, empty); // Frames are always empty at the start
    vector<int> refStr(refStrSize);
    cout << "Enter the reference string (space separated): ";
    for (int i = 0; i < refStrSize; i++)
    {
        cin >> refStr[i];
        lruPageTable[refStr[i]] = empty; // Initializing all pages as not used
    }
    paragraph;

    // Initial Condition:
    refStrPrint(refStr);
    paragraph;
    displayFrames(frames);
    paragraph;

    // Main Simulation:
    int pageFaultCount = pageReplacement(frames, lruPageTable, refStr);
    paragraph;

    cout << "Final Output: " << endl;
    cout << "Total page hits: " << refStrSize - pageFaultCount << endl;
    cout << "Total page faults: " << pageFaultCount << endl;
    displayFrames(frames);

    return 0;
}
