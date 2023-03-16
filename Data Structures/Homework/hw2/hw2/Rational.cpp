#include "Rational.h"
#include <iostream>

using namespace std;
Rational::Rational(int n, int d){
    numer =n;
    denom = d;
    if(denom ==0){
        cout<<"Error";
        exit(0);
    }
    simplify();
}
void Rational::simplify(){
        int g = gcd(numer,denom);
        numer = numer/g;
        denom = denom/g;

}

int Rational::gcd(int n,int d){
    int r;
    if (n>d){
    r=n;
    while(r>0){
        if(n%r ==0 && d%r ==0){
            break;
        }
        r--;
    }
    }
    if(d>n){
        r=d;
        while(r>0){
        if(n%r ==0 && d%r ==0){
            break;
        }
        r--;
    }
    }
    return r;



}
Rational Rational::operator+(const Rational& o)
{
    Rational temp;
    temp.numer = (numer*o.denom) + (o.numer*denom);
    temp.denom = denom * o.denom;
    temp.simplify();
    return temp;
}
Rational Rational::operator-(const Rational& o)
{
    Rational temp;
    temp.numer = (numer*o.denom) - (o.numer*denom);
    temp.denom = denom * o.denom;
    temp.simplify();
    return temp;
}
Rational Rational::operator *(const Rational& o)
{
    Rational temp;
    temp.numer = (numer*o.numer);
    temp.denom = denom * o.denom;
    temp.simplify();
    return temp;
}
Rational Rational::operator /(const Rational& o)
{
    Rational temp;
    temp.numer = (numer*o.denom);
    temp.denom = denom * o.numer;
    temp.simplify();
    return temp;
}

bool Rational::operator<(const Rational & o) const
{
    return this->numer*o.denom < this->denom*o.numer;
}
bool Rational::operator>(const Rational & o) const
{
    return this->numer*o.denom > this->denom*o.numer;
}
bool Rational::operator<=(const Rational & o) const
{
    return this->numer*o.denom <= this->denom*o.numer;
}
bool Rational::operator>=(const Rational & o) const
{
    return this->numer*o.denom >= this->denom*o.numer;
}
bool Rational::operator == (const Rational & o) const
{
    return this->numer*o.denom == this->denom*o.numer;
}
bool Rational::operator!=(const Rational & o) const
{
    return this->numer*o.denom != this->denom*o.numer;
}

ostream& operator <<(ostream& rOs, const Rational& rFrom) {
    rOs << rFrom.numer << "/" << rFrom.denom;
    return rOs;
}

istream& operator >>(istream& in, Rational& r)
{
    char c;

    in >> r.numer;
    in >> c;
    in >> r.denom;

    r.simplify();

    return in;
}


Rational& Rational::operator ++() {
    this->numer=(this->numer + 1);
    this->simplify();
    return *this;
}

Rational Rational::operator ++(int) {
    Rational t = *this;
    this->numer = (this->numer + 1);
    this->simplify();
    return t;
}

Rational& Rational::operator --() {
    this->numer = (this->numer - 1);
    this->simplify();
    return *this;
}

Rational Rational::operator --(int) {
    Rational t = *this;
    this->numer = (this->numer - 1);
    this->simplify();
    return t;
}
