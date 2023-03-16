/**
 * CSC 232 Lab 1
 * Cameron Weston
 * Vamsi Devareddy
 * 6/14/2022
 * @file lab1_Weston_Cameron_Devareddy_Vamsi.cpp
 */

#include <iostream>
#include <memory>

using namespace std;

//prototypes
int* doubleCapacity(const int* list, int size);
void display(int * list, int size);

int main()
{
    int size = 5;
    int *arr = new int[size];
    //unique_ptr<int[]> arr( new int[size]);

    for (int i = 0; i < size; i++)
        {
            arr[i] = i + 1;
        }

    display(arr, size);
    int *tempArr = arr;
    arr = doubleCapacity(arr, size);
    delete [] tempArr;
    tempArr = nullptr;

    for (int i = 5; i < 10; i++)
        {
            arr[i] = i + 1;
        }
    display(arr, size*2);

    delete [] arr;
    arr = nullptr;

    return 0;
}

/**
Function doubleCapacity doubles the capacity of a dynamic array of ints and returns that new array
@param list - dynamic array of ints to be doubled in size
@param size - size of the initial array
@return int pointer to array
*/
int* doubleCapacity(const int* list, int size)
{
    int *newArr = new int[size*2];
    //unique_ptr<int[]> newArr( new int[size*2]);
    for (int i = 0; i < size; i++)
        {
            newArr[i] = list[i];
        }
    return newArr;
}

/**
Function display displays a dynamic array to the console
@param list - list pointer to be diplayed
@param size - size of the array
*/
void display(int * list, int size)
{
    for (int i{0}; i < size; i++)
        {
            cout << list[i] << " ";
        }
    cout << endl;
}
