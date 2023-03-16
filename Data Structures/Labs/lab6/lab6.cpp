/**
 * @file lab6_Weston_Cameron_Abbott_Daniel.cpp
 * @author Cameron Weston
 * @author Douglas Witt
 * @brief CSC 232 - SU22 Lab 6 on exception handling and templates
 * @date 2022-07-04
 */

#include <iostream>

using namespace std;

//prototypes
int getInputSizeOfBag();

template <typename T>
class Bag
{
private:
    int capacity; //maximum capacity, default value is 10
    int currentSize; // current number of values in the bag
    T * list; //array for storing the values in the bag
public:
    Bag(int cap = 10); //constructor
    ~Bag();            //destructor
    bool isFull();     //returns true if list is full
    void add(T value); //if bag is not full, adds a new value at the end of list
    void display();    //prints out the values in the bag
    T findMaximum();   //finds and returns the value of the largest element
};

template <typename T>
Bag<T>::Bag(int cap)
{
    if (cap <= 0 || cap >50)
        capacity = 10;
    else
        capacity = cap;

    list = new T[capacity];
    currentSize = 0;
}

template <typename T>
Bag<T>::~Bag()
{
    delete [] list;
}

template <typename T>
bool Bag<T>::isFull()
{
    return currentSize == capacity;
}

template <typename T>
void Bag<T>::add(T value)
{
    if (isFull())
    {
        cout << "Can not add to a full bag" << endl;
        return;
    }
    else
    {
       list[currentSize] = value;
       currentSize++;
    }
}

template <typename T>
void Bag<T>::display()
{
    cout << endl << "Values in bag: ";
    for (int i =0; i< currentSize; i++)
        cout << list[i] << " ";
    cout << endl << "Largest value is ";
    cout << findMaximum() << endl;
}

template <typename T>
T Bag<T>::findMaximum()
{
    T max = list[0];
    for (int i = 1; i < currentSize; i++)
    {
        if (max < list[i])
        {
            max = list[i];
        }
    }
    return max;
}

int main()
{
    Bag<int> b(5);
    b.add(4);
    b.add(20);
    b.add(-3);
    cout << endl;
    b.display();

    int bagSize;
    bool sizeNotFound = true;
    while (sizeNotFound)
    {
        try
        {
            bagSize = getInputSizeOfBag();
            sizeNotFound = false;
        }
        catch (string exception)
        {
            cout << exception;
        }
    }

    //create bag of strings
    Bag<string> names(bagSize);

    //arbitrary list of first names
    string randomNames[10] = {"Mark", "Daisy", "Ellen", "Alice",
                        "Pat", "Leah", "Doug", "Ashley",
                        "Jessica", "Opal"};

    for (int i = 0;i < bagSize; i++)
    {
        names.add(randomNames[i]);
    }
    names.display();
}

int getInputSizeOfBag()
{
    int size;
    cout << endl << "Enter a value between 1 and 10 for the size of a bag of names: ";
    cin >> size;

    string errorString = "ERROR: Invalid bag size";
    if (size < 1 || size > 10)
    {
        throw errorString;
    }
    else
    {
        return size;
    }
}
