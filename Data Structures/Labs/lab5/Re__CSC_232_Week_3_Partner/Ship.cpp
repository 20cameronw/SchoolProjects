#include "Ship.h"

Ship::Ship()
{
    name = "";
    year = 0;
}


Ship::Ship(string n, int y){
    name= n;
    year = y;
}

Ship::~Ship(){}

int Ship::getYear() const{
    return year;
}
string Ship::getName() const{
    return name;
}
void Ship::print(){
    cout<<"The ship "<<Ship::getName()<<" was built in the year "<<Ship::getYear()<<endl;
}
