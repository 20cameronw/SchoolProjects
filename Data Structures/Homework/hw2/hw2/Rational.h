#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED
#include <iostream>
using namespace std;

class Rational{
protected:
    int denom;
    int numer;
public:
    Rational(){
    numer=0;
    denom=1;
    simplify();
    }
    Rational(int n,int d);
    void simplify();
    static int gcd(int,int);
    Rational operator+(const Rational&);
    Rational operator-(const Rational&);
    Rational operator*(const Rational&);
    Rational operator/(const Rational&);
    bool operator<(const Rational & Rational) const;
    bool operator>(const Rational & Rational) const;
    bool operator<=(const Rational & Rational) const;
    bool operator>=(const Rational & Rational) const;
    bool operator==(const Rational & Rational) const;
    bool operator!=(const Rational & Rational) const;

    friend istream& operator>>(istream&, Rational&);
    friend ostream& operator<<(ostream&,const Rational&);
    Rational& operator ++();
    Rational operator ++(int);

    Rational& operator --();

    Rational operator --(int);



};

#endif // RATIONAL_H_INCLUDED
