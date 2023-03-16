/**
Cameron Weston
Abbott Daniel
CSC 232 - SU22
6/22/2022
*/

#include <iostream>

using namespace std;

enum Month { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

//prototypes
string getMonthName(int);

/**
class DayOfYear takes an integer representing the day of the year
It also stores the corresponding month and day of the month
*/
class DayOfYear
{
private:
    int dayOfYear;
    Month month;
    int dayOfMonth;

public:
    DayOfYear(int day)
    {
        dayOfYear = day;
        findMonthAndDay();
    }

    static int lastDayInt[12];

    //friends
    friend void print(DayOfYear);

    //mutators
    void findMonthAndDay();

    //accessors
    int getDayOfYear() const
    { return dayOfYear; }

    int getDayOfMonth() const
    { return dayOfMonth; }

    int getMonth() const
    { return month; }
};

//declare the integer representation of the last day in each month
int DayOfYear::lastDayInt[] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

/**
Member function findMonthAndDay is called in the DayOfYear constructor
Calculates the month and day of the month given the dayOfYear
*/
void DayOfYear::findMonthAndDay()
{
    //first find and assign the correct month
    for (int monthIndex; monthIndex < DEC; monthIndex++)
    {
        //check if the dayOfYear number is greater than the current month's last day
        if (dayOfYear > lastDayInt[monthIndex])
            continue;

        //if it is not, then record the month, figure the day and stop the loop
        month = static_cast<Month>(monthIndex);
        dayOfMonth = dayOfYear - lastDayInt[month - 1];
        break;
    }
}

/**
function print takes in a DayOfYear object and prints the month
and day of month that is being stored
@param DayOfYear object
*/
void print(DayOfYear dayOfYear)
{
    cout << "Day " << dayOfYear.getDayOfYear() << " would be "
         << getMonthName(dayOfYear.getMonth()) << " " << dayOfYear.getDayOfMonth()
         << endl;
}

int main()
{
    //local variables
    int day;

    while (true)
    {
        cout << endl << "Enter an integer between 1 and 365 for day of year: ";
        cin >> day;
        //check if day is out of bounds and restart if it is
        if (day > 365 || day < 1)
        {
            cout << "Error! Value must be between 1 and 365. Try again.";
            continue;
        }
        DayOfYear dayOfYear(day);
        print(dayOfYear);

    }
    return 0;
}

/**
Function getMonthName takes in a month enum and returns the corresponding month as a string
@param month - month enum
@return corresponding month string
*/
string getMonthName(int month)
{
    switch (month)
    {
        case 0:
            return "January";
            break;
        case 1:
            return "February";
            break;
        case 2:
            return "March";
            break;
        case 3:
            return "April";
            break;
        case 4:
            return "May";
            break;
        case 5:
            return "June";
            break;
        case 6:
            return "July";
            break;
        case 7:
            return "August";
            break;
        case 8:
            return "September";
            break;
        case 9:
            return "October";
            break;
        case 10:
            return "November";
            break;
        case 11:
            return "December";
            break;
        default:
            return "(Invalid month index)";
            break;
    }
}
