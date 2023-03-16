#include <iostream>
#include <string>

using namespace std;

class Ship{
private:
    string name;
    int year;

public:
    //default constructor
    Ship();

    //Constructor
    Ship(string n, int y);

    //Deconstructor
    ~Ship();

    int getYear() const;
    string getName() const;
    virtual void print();

};
#pragma once
