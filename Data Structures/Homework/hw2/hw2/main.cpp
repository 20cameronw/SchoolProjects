#include <iostream>
#include "Rational.cpp"
using namespace std;

int main()
{
    Rational r1(12, 18); // 2/3
    cout << "r1 is " << r1 << endl;
    Rational r2(2, 24); // 1/12
    cout << "r2 is " << r2 << endl;

    cout << "\nTesting the arithmetic operators" << endl;
    Rational r3 = r1 + r2; // 3/4
    cout << r1 << " + " << r2 << " = " << r3 << endl;
    Rational r4 = r3 - r2; // 2/3
    cout << r3 << " - " << r2 << " = " << r4 << endl;
    Rational r5 = r1 * r3; // 1/2
    cout << r1 << " * " << r3 << " = " << r5 << endl;
    Rational r6 = r1 / r2; // 8/1
   cout << r1 << " / " << r2 << " = " << r6 << endl;

    cout << "\nTesting the comparison operators" << endl;
    cout << "Is " << r1 << " == " << r2 << "? " << (r1 == r2) << endl;
    cout << "Is " << r1 << " != " << r2 << "? " << (r1 != r2) << endl;
    cout << "Is " << r1 << " < " << r2 << "? " << (r1 < r2) << endl;
    cout << "Is " << r1 << " <= " << r2 << "? " << (r1 <= r2) << endl;
    cout << "Is " << r1 << " > " << r2 << "? " << (r1 > r2) << endl;
    cout << "Is " << r1 << " >= " << r2 << "? " << (r1 >= r2) << endl;

    cout << "\nTesting the extraction operator" << endl;
    cout << "Enter a rational number in the form a/b ";
    cin >> r1;
    cout <<"This rational is equal to " << r1 << endl;

    cout << "\nTesting the pre-increment operator" << endl;
    cout << "r2 is " << r2 << endl;
    cout << "r3 is " << r3 << endl;
    r3 = ++r2;
    cout << "After executing r3 = ++r2" << endl;
    cout << "r2 is " << r2 << endl;
    cout << "r3 is " << r3 << endl;

    cout << "\nTesting the post-increment operator" << endl;
    r3 = r2++;
    cout << "After executing r3 = r2++" << endl;
    cout << "r2 is " << r2 << endl;
    cout << "r3 is " << r3 << endl;

    cout << "\nTesting the pre-decrement operator" << endl;
    Rational r7(5, 6);
    cout << "r7 is " << r7 << endl;
    cout << "r1 is " << r1 << endl;
    r1 = --r7;
    cout << "After executing r1 = --r7" << endl;
    cout << "r1 is " << r1 << endl;
    cout << "r7 is " << r7 << endl;

    cout << "\nTesting the post-decrement operator" << endl;
    r1 = r7--;
    cout << "After executing r1 = r7--" << endl;
    cout << "r1 is " << r1 << endl;
    cout << "r7 is " << r7 << endl;

    return 0;
}
