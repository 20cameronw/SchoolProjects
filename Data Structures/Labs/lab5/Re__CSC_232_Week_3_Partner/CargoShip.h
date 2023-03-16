#include <iostream>
#include <string>
#include "Ship.h"

using namespace std;

class CargoShip: public Ship
{
private:
    int capacityInTons;

public:
    //default constructor
    CargoShip();

    //constructor
    CargoShip(string n, int y, int p);

    int getCapacity() const;
    virtual void print();
};
