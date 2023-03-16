/**
Cameron Weston
Daniel Abbott
CSC 232 - SU22
Lab 3
6/22/2022
*/

#include <iostream>

using namespace std;

class Circle
{
private:
    double radius;
public:
    const double PI = 3.14159;

    //default constructor
    Circle()
        {
            radius = 0.0;
        }

    //constructor #2
    Circle(double r)
        {
            radius = r;
        }

    //mutator functions
    void setRadius(double);

    //accessor functions
    double getRadius() const
    { return radius; }

    double getArea() const
    { return PI * radius * radius; }

    double getDiameter() const
    { return radius * 2; }

    double getCircumference() const
    { return 2 * PI * radius; }
};

void Circle::setRadius(double r)
{
    if (r >= 0)
        radius = r;
    else
    {
        cout << "Invalid radius\n";
        exit(EXIT_FAILURE);
    }
}


int main()
{
    //local variables
    double radius;

    //create circle object with default constructor
    Circle circle;

    //display initial data for circle
    cout << "Here is the first circle's data after using the default constructor for creating the circle: ";
    cout << endl << "Radius: " << circle.getRadius();
    cout << endl << "Diameter: " << circle.getDiameter();
    cout << endl << "Area: " << circle.getArea();
    cout << endl << "Circumference: " << circle.getCircumference() << endl;

    //get input radius
    cout << endl << "What value do you want to set the radius to? ";
    cin >> radius;
    circle.setRadius(radius);

    //display data back to user
    cout << endl << "Here is the first circle's data after setting the radius to "
                    << radius << ": ";
    cout << endl << "Radius: " << circle.getRadius();
    cout << endl << "Diameter: " << circle.getDiameter();
    cout << endl << "Area: " << circle.getArea();
    cout << endl << "Circumference: " << circle.getCircumference() << endl;

    //create second circle
    Circle secondCircle(12.5);

    //report second circle
    cout << endl << "Here is the second circle's data: ";
    cout << endl << "Radius: " << secondCircle.getRadius();
    cout << endl << "Diameter: " << secondCircle.getDiameter();
    cout << endl << "Area: " << secondCircle.getArea();
    cout << endl << "Circumference: " << secondCircle.getCircumference() << endl;

    return 0;
}
