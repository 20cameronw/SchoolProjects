/**
 * Author: Cameron Weston
 * Course: CSC 360 Operating Systems
 * Assignment: Project 5 - Bankers algorithm
 * Due: Sunday, October 23, 2022 - 11:59 PM
 * Instructor: Dr. Siming Liu
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
 File contents:

 number of processes: n
 number of resource types: m
 An n x m allocation matrix
 An n x m max matrix
 A 1 x m available vector
 A i : 1 x m request vector
 */

string fileLocation;

int main(int argc, const char* argv[]) {
    fileLocation = argv[1];

    int numProcesses, numResourceTypes;
    int** allocationMatrix;
    int** maxMatrix;
    int** needMatrix;
    vector<int> available;
    vector<int> request;
    int requestingP;

    //open the file
    ifstream inputFile(fileLocation);
    if (!inputFile.is_open())
    {
        cout << "ERROR: Could not open file.\n";
        return 1;
    }

    //read in number of processes and number of resource types
    inputFile >> numProcesses;
    cout << "There are " << numProcesses << " processes in the system.\n\n";

    inputFile >> numResourceTypes;
    cout << "There are " << numResourceTypes << " resource types.\n\n";

    //allocate memory
    allocationMatrix = new int* [numProcesses];
    for (int i = 0; i < numProcesses; i++)
        allocationMatrix[i] = new int[numResourceTypes];
    maxMatrix = new int* [numProcesses];
    for (int i = 0; i < numProcesses; i++)
        maxMatrix[i] = new int[numResourceTypes];
    needMatrix = new int* [numProcesses];
    for (int i = 0; i < numProcesses; i++)
        needMatrix[i] = new int[numResourceTypes];

    //read and print allocation matrix
    cout << "The Allocation Matrix is...\n   ";
    for (int i = 65; i < 65 + numResourceTypes; i++)
        cout << (char)i << " ";
    cout << endl;

    for (int i = 0; i < numProcesses; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < numResourceTypes; j++)
        {
            inputFile >> allocationMatrix[i][j];
            cout << allocationMatrix[i][j] << " ";
        }
        cout << endl;
    }

    //read and print max matrix
    cout << endl << "The Max Matrix is...\n   ";
    for (int i = 65; i < 65 + numResourceTypes; i++)
        cout << (char)i << " ";
    cout << endl;

    for (int i = 0; i < numProcesses; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < numResourceTypes; j++)
        {
            inputFile >> maxMatrix[i][j];
            cout << maxMatrix[i][j] << " ";
        }
        cout << endl;
    }

    //calculate and print need matrix
    cout << endl << "The Need Matrix is...\n   ";
    for (int i = 65; i < 65 + numResourceTypes; i++)
        cout << (char)i << " ";
    cout << endl;

    for (int i = 0; i < numProcesses; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < numResourceTypes; j++)
        {
            needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
            cout << needMatrix[i][j] << " ";
        }

        cout << endl;
    }

    //read in and print the available vector
    cout << endl << "The Available Vector is...\n";
    for (int i = 65; i < 65 + numResourceTypes; i++)
        cout << (char)i << " ";
    cout << endl;

    for (int i = 0; i < numResourceTypes; i++)
    {
        int temp;
        inputFile >> temp;
        available.push_back(temp);
    }

    for (auto it : available)
        cout << it << " ";

    cout << endl << endl;

    //calculate if the system is in a safe state
    vector<int> work = available;
    vector<bool> finish(numProcesses, false);
    int foundIndex = -1;

    for (int i = 0; i < numProcesses; i++)
    {
        if (finish[i] == true) //skip this process if finished
            continue;

        vector<int> localNeed;
        for (int j = 0; j < numResourceTypes; j++)
            localNeed.push_back(needMatrix[i][j]);

        if (localNeed <= work)
        {
            foundIndex = i;
            vector<int> allocationI;
            for (int x = 0; x < numResourceTypes; x++)
            {
                allocationI.push_back(allocationMatrix[i][x]);
            }

            for (int x = 0; x < numResourceTypes; x++)
            {
                work[x] += allocationI[x];
            }

            finish[i] = true;
        }
        else continue;
    }

    bool safe = true;

    for (auto it : finish)
    {
        if (it == false)
            safe = false;
    }

    if (safe)
    {
        cout << "THE SYSTEM IS IN A SAFE STATE.\n\n";
    }
    else
    {
        cout << "THE SYSTEM IS NOT IN A SAFE STATE.\n\n";
    }

    //read and print the request vector
    cout << "The Request Vector is...\n  ";
    for (int i = 65; i < 65 + numResourceTypes; i++)
        cout << (char)i << " ";

    string requester;
    getline(inputFile, requester, ':');
    int requesterIndex = stoi(requester);
    cout << endl << requesterIndex << ":";

    for (int i = 0; i < numResourceTypes; i++)
    {
        int temp;
        inputFile >> temp;
        request.push_back(temp);
    }
     
    for (auto it : request)
        cout << it << " ";

    cout << endl << endl;

    if (request <= available)
    {
        cout << "THE REQUEST CAN BE GRANTED!\n\n";
    }
    else
    {
        cout << "THE REQUEST CANNOT BE GRANTED!.\n\n";
    }

    //available = available - request
    for (int i = 0; i < numResourceTypes; i++)
    {
        available[i] -= request[i];
    }

    cout << "The Available Vector is...\n";
    for (auto it : available)
        cout << it << " ";

    cout << endl << endl;

    //deallocate memory and close the file
    for (int i = 0; i < numProcesses; i++)
        delete[] maxMatrix[i];
    delete[] maxMatrix;

    for (int i = 0; i < numProcesses; i++)
        delete[] allocationMatrix[i];
    delete[] allocationMatrix;

    for (int i = 0; i < numProcesses; i++)
        delete[] needMatrix[i];
    delete[] needMatrix;

    inputFile.close();

    return 0;

}