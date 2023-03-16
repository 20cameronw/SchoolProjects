/**
Cameron Weston
CSC 232 - SU22
Lab 8
7/14/2022
*/

#include <iostream>
#include <string>
#include <forward_list>
#include <list>

using namespace std;

int main()
{
    //#1
    forward_list<string> names1 = {"Mark", "Mary", "James"};

    //#2
    names1.push_front("Susan");
    names1.push_front("Eric");

    //#3
    for (auto it = names1.cbegin(); it != names1.cend(); it++)
        cout << *it << " ";

    cout << endl;

    //#4
    list<string> names2;

    //#5
    names2.insert(names2.begin(), names1.begin(), names1.end());

    //#6
    for (auto rit = names2.crbegin(); rit != names2.crend(); rit++)
        cout << *rit << " ";
    cout << endl;

    //#7
    auto it = names2.begin();
    for (; it != names2.end(); it++)
    {
        if (*it == "Susan")
            break;
    }
    //cout << endl << *it;
    auto it2 = names2.erase(it);

    //#8
    cout << endl << "Contents after deleting Susan is: " << endl;
    for (auto element : names2)
        cout << element << " ";
    cout << endl;

    //#9
    auto it3 = names2.insert(it2, "Tracy");
    it3--;
    cout << endl << "Contents after inserting Tracy is: " << endl;
    for (auto element : names2)
        cout << element << " ";
    cout << endl;

    //#10
    names2.insert(it3, "John");
    cout << endl << "Contents after inserting John is: " << endl;
    for (auto element : names2)
        cout << element << " ";
    cout << endl;

    return 0;
}
