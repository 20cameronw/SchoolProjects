/**
* Authors: Cameron Weston
* Course: CSC 525 Lab 6 B
* Last Modified Date: 10/1/2022
* Description: File IO - Converts a text file to binary file 
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
#include <sstream>

using namespace std;

int main()
{
	string folder = "C:\\Temp\\";
	string fileName;
	cout << "This program converts a text file to a binary file (.bin)\n";
	cout << "Please enter a file name without the extension: ";
	cin >> fileName;

	string fullLocation = folder + fileName + ".txt";

	//open the file
	ifstream file;
	file.open(fullLocation);

	//check if file is open and end program if not
	if (!file.is_open())
	{
		cout << "\nERROR: File failed to open at location " << fullLocation << endl;
		return 1;
	}

	int* numberOfNumbers = new int;
	file.read((char*)numberOfNumbers, sizeof(int));
	cout << *numberOfNumbers;
	//float* numbersRead;



	file.close();
	//delete[] numbersRead;

	return 0;

}