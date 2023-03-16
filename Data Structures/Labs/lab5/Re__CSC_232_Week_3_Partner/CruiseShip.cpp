#include "CruiseShip.h"

CruiseShip::CruiseShip()
{
    passengers = 100;
}

CruiseShip::CruiseShip(string n, int y, int p):Ship(n,y){
    passengers = p;
}
int CruiseShip::getPassengers() const{
    return passengers;
}
void CruiseShip::print(){
    cout<< "The cruise ship " << getName()
    << " can have a maximum of " << passengers << " passengers" <<endl;
}
