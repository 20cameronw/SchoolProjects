/*********************************************************************
 * Author: Cameron Weston
 * Course: CSC 360 Operating Systems
 * Intstructor: Dr. Siming Liu
 * Due: 11/9/2022
 * Description: Project 6 - Simulating different page replacement algorithms
 * Notes:
 *    - I'm check that the input file will contain exactly 2 different algorithms
 *    - I couldn't get the OPT algorithm to be most optimal
*/

#include <iostream>
#include <string>
#include <fstream>
#include "PageReplacer.h"

using namespace std;

int main(int argc, char** argv)
{
    //check for correct number of command line arguments
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    //read command line arguments
    const string FILENAME = argv[1];

    //read the file
    ifstream file(FILENAME);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    //read the file line by line
    string line;
    int lineCount = 0;
    string referenceString;
    int numFrames;
    string algorithm1;
    string algorithm2;
    while (getline(file, line))
    {
        if (lineCount == 0)
        {
            referenceString = line;
        }
        else if (lineCount == 1)
        {
            numFrames = stoi(line);
        }
        else if (lineCount == 2)
        {
            algorithm1 = line;
        }
        else if (lineCount == 3)
        {
            algorithm2 = line;
        }
        else
        {
            cout << "Error: too many lines in file" << endl;
            return 1;
        }
        lineCount++;
    }

    //print the starting information (reference string, number of frames)
    cout << "Reference String: " << endl << referenceString << endl;
    cout << "Number of Frames: " << numFrames << endl;

    //create the page replacer object
    PageReplacer pageReplacer1(algorithm1, numFrames, referenceString);
    PageReplacer pageReplacer2(algorithm2, numFrames, referenceString);

    //run the page replacer
    pageReplacer1.run();
    pageReplacer2.run();

    //close the file
    file.close();
    return 0;
} //main