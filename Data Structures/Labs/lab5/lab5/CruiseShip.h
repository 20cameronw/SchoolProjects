#include <iostream>
#include <string>
#include "Ship.h"

using namespace std;

class CruiseShip: public Ship
{
private:
    int passengers;

public:
    //default constructor
    CruiseShip();

    //constructor
    CruiseShip(string n, int y, int p);

    int getPassengers() const;
    virtual void print();
};
