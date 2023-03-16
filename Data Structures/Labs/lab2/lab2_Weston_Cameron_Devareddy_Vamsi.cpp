/**
 * CSC 232 Lab 2
 * Cameron Weston
 * Vamsi Devareddy
 * 6/14/2022
 * @file lab2_Weston_Cameron_Devareddy_Vamsi.cpp
 */

#include <iostream>
#include <memory>
#include <iomanip>
using namespace std;

enum Month {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER,
        OCTOBER, NOVEMBER, DECEMBER};

struct MonthData
{
    double totalRainfall;
    double avgTemperature;
};

//prototypes
string getMonthName(const Month &month);
MonthData getYearData(MonthData *monthData);

int main()
{
    MonthData * monthData = new MonthData[12];

    //load data from user
    for (Month month = JANUARY; month <= DECEMBER;
            month = static_cast<Month>(month+1))
    {
        string currentMonth = getMonthName(month);
        cout << "Enter the total rainfall in inches for the month of "
            << currentMonth << ": ";
        cin >> monthData[month].totalRainfall;
        cout << "Enter the average temperature in Fahrenheit for the month of "
            << currentMonth << ": ";
        cin >> monthData[month].avgTemperature;
        cout << endl;
    }

    MonthData yearData = getYearData(monthData);
    cout << fixed << showpoint << setprecision(2);
    cout << "The total yearly rainfall is " << yearData.totalRainfall << endl;
    cout << "The average yearly daytime temperature is " << yearData.avgTemperature
         << endl;

    delete [] monthData;
    return 0;
}

/**
Function getMonthName takes in a month enum and returns the corresponding month as a string
@param month - month enum
@return corresponding month string
*/
string getMonthName(const Month &month)
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

/**
Function getYearData calculates and returns aggregate data of all 12 months
@param monthData - dynamic array of month structs
@return MonthData - returns a struct containing the aggregate data for the year
*/
MonthData getYearData(MonthData *monthData)
{
    MonthData yearData;

    //local variables
    double rainfallTotal;
    double temperatureAvg;

    for (Month month = JANUARY; month <= DECEMBER;
            month = static_cast<Month>(month+1))
    {
        rainfallTotal += monthData[month].totalRainfall;
        temperatureAvg += monthData[month].avgTemperature;
    }
    temperatureAvg /= 12;

    yearData.totalRainfall = rainfallTotal;
    yearData.avgTemperature = temperatureAvg;

    return yearData;
}
