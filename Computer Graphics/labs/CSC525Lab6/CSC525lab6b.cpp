
#include <iostream> 
#include <fstream> 
void readfile();
void convert1();
int points_arr[10000];
int array_size = 0;
std::string filename;
int main()
{
	std::cout << ".txt to binary!\n";
	readfile();
	convert1();
}
void readfile()
{
	std::cout << "what is file name *do not include .txt*\n";
	std::cin >> filename;
	std::fstream myfile("C:\\" + filename + ".txt", std::ios_base::in); float a;
	// fill the array with data from textfile
	while (myfile >> a)
	{
		points_arr[array_size] = a;
		std::cout << "\nthe " << i + 1 << "number is " << a; array_size++;

	}
	// display array contents
	std::cout << "the size of the array is " << points_arr[0] << "\n"; for (int j = 1; j < array_size; j++)
	{
		std::cout << "result " << j << " is " << points_arr[j] << "\n";
	}
	void convert1()
	{
		std::ifstream in("C:\\" + filename + ".txt");
		std::ofstream out("C:\\" + filename + ".bin", std::ios::binary); double d;

		int c = 0; // counts the values10 per line
		while (in >> d) {
			if (c <= 10) {
				out.write((char*)&d, sizeof d); c++;
			}
			else {
				c = 0;
				std::cout << std::endl; out.write((char*)&d, sizeof d); c++;
			}
		}
		std::cout << "conversion complete";
	}