//This is the implementation file for the PageReplacer Class
//This class is used to simulate different page replacement algorithms
//Algoritgms include: FIFO, LRU, OPT, and RAND

#include "PageReplacer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;


//Constructor
PageReplacer :: PageReplacer(string algorithmType, int numFrames, string referenceString)
{
    setAlgorithmType(algorithmType);
    setNumFrames(numFrames);
    setReferenceArray(referenceString);
}

//Destructor
PageReplacer :: ~PageReplacer()
{
    delete [] referenceArray;
}

//Setters
void PageReplacer :: setAlgorithmType(string algorithmType)
{
    this->algorithmType = algorithmType;
}

void PageReplacer :: setNumFrames(int numFrames)
{
    this->numFrames = numFrames;
}

/**
 * SetReferenceArray allocates enough memory for the reference array
 * and reads the reference string into the reference array
 *
 * Parameters:
 *      string referenceString: the reference string
*/
void PageReplacer :: setReferenceArray(string referenceString)
{
    //create a string stream from the reference string
    stringstream ss(referenceString);

    //read the string stream into the local vector
    vector<int> referenceVector;
    int number;
    while (ss >> number)
    {
        referenceVector.push_back(number);
    }

    //cout << "Size of reference vector: " << sizeof(referenceVector) << endl;
    referenceArraySize = sizeof(referenceVector);

    //allocate memory for the reference array
    referenceArray = new int[referenceArraySize];

    //set the reference array
    for (int i = 0; i < referenceVector.size(); i++)
    {
        referenceArray[i] = referenceVector[i];
    }

    //find the max page number
    int max = 0;
    for (int i = 0; i < referenceArraySize; i++)
    {
        if (referenceArray[i] > max)
        {
            max = referenceArray[i];
        }
    }

    //set the max page number
    maxPageNumber = max;
}

//Page replacement algorithms

/**
 * First In First Out Algorithm
 *
 * Parameters:
 *      int frames: the number of frames
 *
 * Returns:
 *      int: the number of page faults
*/
int PageReplacer :: FIFO(int frames) const
{
    int pageFaults = 0;
    queue<int> frameQueue;

    for (int i = 0; i < frames; i++)
    {
        frameQueue.push(referenceArray[i]);
        pageFaults++;
    }

    for (int i = frames; i < referenceArraySize; i++)
    {
        if (existsInQueue(frameQueue, referenceArray[i])) //page hit
        {
            //do nothing
        }
        else //page fault
        {
            //remove front of queue
            frameQueue.pop();
            //add to back of queue
            frameQueue.push(referenceArray[i]);
            //increment page faults
            pageFaults++;
        }
    }

    return pageFaults;
}


/**
 * Least Recently Used Algorithm
 *
 * Parameters:
 *      int frames: the number of frames
 *
 * Returns:
 *      int: the number of page faults
*/
int PageReplacer :: LRU(int frames) const
{
    int pageFaults = 0;

    //each page entry has a counter
    int* pageEntryCounter = new int[maxPageNumber];

    int* frameArray = new int[frames];


    //the first frames are all page faults
    for (int i = 0; i < frames; i++)
    {
        pageEntryCounter[referenceArray[i]] = i;
        frameArray[i] = referenceArray[i];
        pageFaults++;
    }

    //loop through the rest of the reference array
    for (int i = frames; i < referenceArraySize; i++)
    {
        int currentPage = referenceArray[i];
        //if the page is in the frame array
        if (existsInArray(frameArray, currentPage))
        {
            //update the page entry counter
            pageEntryCounter[currentPage] = i;
        }
        else //page fault
        {
            //find the page with the lowest counter
            int lowestCounter = pageEntryCounter[frameArray[0]];
            int lowestCounterIndex = 0;
            for (int j = 1; j < frames; j++)
            {
                if (pageEntryCounter[frameArray[j]] < lowestCounter)
                {
                    lowestCounter = pageEntryCounter[frameArray[j]];
                    lowestCounterIndex = j;
                }
            }

            //replace the page with the lowest counter
            frameArray[lowestCounterIndex] = currentPage;
            pageEntryCounter[currentPage] = i;
            pageFaults++;
        }
    }


    //deallocate memory
    delete [] pageEntryCounter;
    delete [] frameArray;

    return pageFaults;
}

/**
 * Optimal Algorithm
 *
 * Parameters:
 *      int frames: the number of frames
 *
 * Returns:
 *      int: the number of page faults
*/
int PageReplacer :: OPT(int frames) const
{
    int pageFaults = 0;

    int* frameArray = new int[frames];

    //the first frames are all page faults
    for (int i = 0; i < frames; i++)
    {
        frameArray[i] = referenceArray[i];
        pageFaults++;
    }

    //loop through the rest of the reference array
    for (int i = frames; i < referenceArraySize; i++)
    {
        int currentPage = referenceArray[i];
        
        if (existsInArray(frameArray, currentPage)) //page hit
        {
            //do nothing
        }
        else //page fault
        {
            //find the page that will be used the furthest in the future or never again
            int furthestIndex = 0;
            int furthestPage = frameArray[0];
            for (int j = 1; j < frames; j++)
            {
                int futureIndex = findFutureIndex(frameArray[j], i);
                //if the next page call is greater than current furthest index or its never used again
                if (futureIndex == -1)
                {
                    furthestIndex = futureIndex;
                    furthestPage = frameArray[j];
                    break; //no need to continue because this is the best frame to replace
                }
                else if (futureIndex > furthestIndex)
                {
                    furthestIndex = futureIndex;
                    furthestPage = frameArray[j];
                }
            }

            //replace the page that will be used the furthest in the future
            for (int j = 0; j < frames; j++)
            {
                if (frameArray[j] == furthestPage)
                {
                    frameArray[j] = currentPage;
                }
            }

            pageFaults++;
        }
    }

    delete [] frameArray;

    return pageFaults;
}

/**
 * Random Algorithm
 *
 * Parameters:
 *      int frames: the number of frames
 *
 * Returns:
 *      int: the number of page faults
*/
int PageReplacer :: RAND(int frames) const
{
    int* frameArray = new int[frames];
    int pageFaults = 0;

    //the first frames are all page faults
    for (int i = 0; i < frames; i++)
    {
        frameArray[i] = referenceArray[i];
        pageFaults++;
    }

    //loop through the rest of the reference array
    for (int i = frames; i < referenceArraySize; i++)
    {
        int currentPage = referenceArray[i];
        if (existsInArray(frameArray, currentPage)) //page hit
        {
            //do nothing
        }
        else //page fault
        {
            //replace a random frame
            int randomIndex = rand() % frames;
            frameArray[randomIndex] = currentPage;
            pageFaults++;
        }
    }

    delete [] frameArray;

    return pageFaults;
}

/**
 * run runs the page replacement algorithm
*/
void PageReplacer :: run() const
{
    int pageFaults = 0;
    if (algorithmType == "FIFO")
    {
        pageFaults = FIFO(numFrames);
    }
    else if (algorithmType == "LRU")
    {
        pageFaults = LRU(numFrames);
    }
    else if (algorithmType == "OPT")
    {
        pageFaults = OPT(numFrames);
    }
    else if (algorithmType == "RAND")
    {
        pageFaults = RAND(numFrames);
    }
    else
    {
        cout << "Error: invalid algorithm type" << endl;
        return;
    }

    cout << algorithmType << ": " << pageFaults << endl;
}

/**
 * exisingInQueue checks if a page is in a queue
 *
 * Parameters:
 *      queue<int> frameQueue: the queue of pages
 *      int page: the page to check
 *
 * Returns:
 *      bool: true if the page is in the queue, false otherwise
*/
bool PageReplacer :: existsInQueue(queue<int> frameQueue, int page) const
{
    while (!frameQueue.empty())
    {
        if (frameQueue.front() == page)
        {
            return true;
        }
        frameQueue.pop();
    }
    return false;
}

/**
 * Checks if a page is in an array
 *
 * Parameters:
 *      int* pageArray: the array of pages
 *      int page: the page to check
 *
 * Returns:
 *      bool: true if the page is in the array, false otherwise
*/
bool PageReplacer :: existsInArray(int* pageArray, int page) const
{
    for (int i = 0; i < numFrames; i++)
    {
        if (pageArray[i] == page)
        {
            return true;
        }
    }
    return false;
}

/**
 * Finds the index of the next page call in the reference array
 *
 * Parameters:
 *      int currentIndex: the current index in the reference array
 *
 * Returns:
 *      int: the index of the next page call in the reference array
 *          -1 if the page is never used again
*/
int PageReplacer :: findFutureIndex(int searchPage, int startingPoint) const
{
    int index = -1;
    for (int i = startingPoint + 1; i < referenceArraySize; i++)
    {
        if (referenceArray[i] == searchPage)
        {
            index = i;
            return index;
        }
    }
    return index;
}