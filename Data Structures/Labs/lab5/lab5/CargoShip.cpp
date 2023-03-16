#include "CargoShip.h"

CargoShip::CargoShip()
{
    capacityInTons = 1000;
}

CargoShip::CargoShip(string n, int y, int p):Ship(n,y){
    capacityInTons = p;
}
int CargoShip::getCapacity() const{
    return capacityInTons;
}
void CargoShip::print(){
    cout << "The cargo ship " << getName()
    << " has a maximum capacity of " << capacityInTons << " tons" << endl;
}
