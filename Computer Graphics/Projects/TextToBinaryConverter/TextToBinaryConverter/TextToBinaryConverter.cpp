#include <fstream>
#include <string>
#include <iostream>

using namespace std;

string infileName = "C:\\Temp\\converted_image.txt";
string outfileName = "C:\\Temp\\output.bin";

int main()
{
	ifstream inFile;
	inFile.open(infileName, ios::in);

	ofstream outFile;
	outFile.open(outfileName, ios::binary);

	if (inFile.is_open())
	{
		char ch;
		while (!inFile.eof())
		{
			inFile.get(ch);
			outFile.write((char*)ch, sizeof(ch));
		}
	}
	else
	{
		cout << "Could not open file" << endl;
	}

	inFile.close();
	outFile.close();
	return 0;
}