#include <iostream>
#include <string>
#include "Ship.cpp"
#include "CruiseShip.cpp"
#include "CargoShip.cpp"

using namespace std;

int main()
{
    Ship *ships[3];

    ships[0]=new Ship("Santa Maria", 2010);
    ships[1]=new CruiseShip("Royal Princess", 2000, 600);
    ships[2] = new CargoShip("Panamax", 2020, 1000);
    for(int i=0;i<3;i++) {ships[i]->print();}

    delete [] ships;
    ships = nullptr;

    return 0;
}
