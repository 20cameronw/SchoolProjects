#include <iostream>
#include <string>
#include "Ship.cpp"
#include "CruiseShip.cpp"
#include "CargoShip.cpp"

using namespace std;

int main()
{
    Ship *ships[3];

    ships[0]=new Ship("Ship ",2010);
    ships[1]=new CruiseShip("Cruise Ship",2000,600);
    ships[2] = new CargoShip("Cargo Ship", 2020, 1000);
    for(int i=0;i<3;i++) {ships[i]->print();}
    //system("pause");
    return 0;
}
