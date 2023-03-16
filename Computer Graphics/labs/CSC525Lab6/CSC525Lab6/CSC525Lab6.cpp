/**
* Authors: Cameron Weston
* Course: CSC 525 Lab 6 A
* Last Modified Date: 10/1/2022
* Description: File IO - Converts a binary file to text file
* File: CSC525Lab6.cpp
* IDE / Compiler : Microsoft Visual Studio 2019
* INSTRUCTION FOR COMPILATION AND EXECUTION:
*	1. Double click on CSC525Lab6.sln (the solution file in my VS project) to OPEN the project
*	2. Press Ctrl+F7 to COMPILE
*	3. Press Ctrl+F5 to EXECUTE
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	string folder = "C:\\Temp\\";
	string fileName;
	cout << "This program converts a binary (.bin) file to a text file.\n";
	cout << "Please enter a file name without the extension: ";
	cin >> fileName;

	string fullLocation = folder + fileName + ".bin";

	//open the file
	ifstream file;
	file.open(fullLocation, ios::in | ios::binary);

	//check if file is open and end program if not
	if (!file.is_open())
	{
		cout << "\nERROR: File failed to open at location " << fullLocation << endl;
		return 1;
	}

	//read the first integer from the file
	//it is this number of numbers that the file holds
	int* numbersToRead = new int;
	file.read((char*)numbersToRead, sizeof(int));
	cout << endl << "Numbers to read: " << *numbersToRead << endl;

	//initialize float array
	float* numbersRead = new float[*numbersToRead];

	//get numbersToRead numbers from the file
	file.read((char*)numbersRead, *numbersToRead * sizeof(float));

	//print out numbers
	cout << endl << "Read numbers: " << endl;
	cout << setprecision(2) << fixed;
	for (int i = 0; i < *numbersToRead; i++)
	{
		cout << numbersRead[i] << " ";
	}
	cout << endl;

	//store the information into a text file
	string outputFileName = folder + "copy_of_" + fileName + ".txt";
	ofstream outputFile(outputFileName);

	int numberOfLines = (*numbersToRead / 10);
	//int numbersOnLastLine = *numbersToRead % 10;

	outputFile << *numbersToRead << endl;
	int index = 0;

	outputFile << setprecision(2) << fixed;
	for (int i = 1; i < numberOfLines + 1; i++)
	{
		for (; index < 10 * i; index++)
		{
			outputFile << " " << numbersRead[index] << " ";
		}
		outputFile << endl;
	}

	for (; index < *numbersToRead; index++)
	{
		outputFile << " " << numbersRead[index] << " ";
	}


	//close the files and deallocate memory
	outputFile.close();
	file.close();
	delete numbersToRead;
	delete[] numbersRead;

	return 0;
}