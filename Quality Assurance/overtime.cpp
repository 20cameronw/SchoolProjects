#include <iostream>
using namespace std;
/**
 * Cameron Weston
 * CSC 455 HW 1
 */
// compite this code using g++
// use ada.missouristate.edu or colossus.missouristate.edu
int main() 
{
    float r_pay;
	float h_overtime;
	float over_pay;
	float th_hours;
    
	cout << "Please Enter the hourly regular rate ( $/per hour): ";
	cin >> r_pay;
	if (r_pay <= 0)
		return -1;
    cout << "Please Enter the number overtime hours: ";
    cin >> h_overtime;
	if (h_overtime < 0 || h_overtime > 10)
		return -1;
	cout << "Please Enter the number hours threshold: ";
    cin >> th_hours;
	if (th_hours < 0 || th_hours > 10)
		return -1;


	if (h_overtime <= th_hours)
	{
		over_pay = h_overtime * (r_pay * 1.15);
		cout <<"you worked: " << h_overtime <<" hours" << endl;
		cout <<"you will receive: " << over_pay <<" $" << endl;
	}
	else
	{
		if (h_overtime <= 2)
		{
			over_pay = h_overtime * (r_pay * 1.2);
			cout <<"you worked: " << h_overtime <<" hours" << endl;
			cout <<"you will receive: " << over_pay <<" $" << endl;
		}
		else
		{
			over_pay = 2 * (r_pay * 1.2);
			h_overtime -= 2;
			over_pay += h_overtime * (r_pay * 1.4);
			cout <<"you worked: " << h_overtime + 2 <<" hours" << endl;
			cout <<"you will receive: " << over_pay <<" $" << endl;
		}
	}
    return 0;
}