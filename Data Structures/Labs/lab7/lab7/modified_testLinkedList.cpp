// This program demonstrates the linked list template.
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
   // Define a LinkedList object.
   LinkedList<int> list;

   // Insert few values
   list.insertNode(10);
   list.insertNode(15);
   list.insertNode(5);
   list.insertNode(25);
   list.insertNode(20);
   list.insertNode(50);
   list.insertNode(40);
   list.insertNode(25);
   list.insertNode(30);
   // Display the values in the list.
   cout << "Here are the nodes now.\n";
   list.displayList();
   cout << endl;

   // Test search() member function
   cout << "Searching for 5 " << list.search(5) << endl;
   cout << "Searching for 25 " << list.search(25) << endl;
   cout << "Searching for 50 " << list.search(50) << endl;
   cout << "Searching for 1 " << list.search(1) << endl;
   cout << "Searching for 31 " << list.search(31) << endl;
   cout << "Searching for 71 " << list.search(71) << endl;

   // Test countNodes() member function
   cout << "\nNumber of nodes in the list is " << list.countNodes() << endl;

   //---------------
   cout << "\nTesting copy constructor " << endl;
   LinkedList<int> secondList(list);
   cout << "\nHere is the second list: ";
   secondList.displayList();

   //Modify the second list
   secondList.deleteNode(50); //delete last node
   secondList.deleteNode(5); //delete first node
   secondList.insertNode(1); //insert new first node

   // Display both lists
   cout << "\nHere is the second list after updates: ";
   secondList.displayList();
   cout << "\nHere is the first list: ";
   list.displayList();
   //--------------

   // Test deleteByPosition member function
   cout << "\nCalling deleteByPosition(-2) ---> ";
   list.deleteByPosition(-2);
   cout << "Calling deleteByPosition(100) ---> ";
   list.deleteByPosition(100);
   cout << "Calling deleteByPosition(9) ---> ";
   list.deleteByPosition(9);
   cout << "Calling deleteByPosition(8) " << endl;
   list.deleteByPosition(8);
   cout << "Here are the nodes now: ";
   list.displayList();
   cout << "Calling deleteByPosition(0) " << endl;
   list.deleteByPosition(0);
   cout << "Here are the nodes now: ";
   list.displayList();
   cout << "Calling deleteByPosition(4) " << endl;
   list.deleteByPosition(4);
   cout << "\nHere are the nodes now: ";
   list.displayList();
   cout << endl;

   // Test insertByPosition member function
   cout << "Calling insertByPosition(0, 200) ---> "; list.insertByPosition(0, 200);
   cout << "\nCalling insertByPosition(-5, 200) ---> "; list.insertByPosition(-5, 200);
   cout << endl << endl;

   cout << "Calling insertByPosition(3, -100) ---> "; list.insertByPosition(3, -100);
   cout << "\nCalling insertByPosition(10, -100) ---> "; list.insertByPosition(10, -100);
   cout << endl << endl;

   cout << "Calling insertByPosition(2, 77) ---> "; list.insertByPosition(2, 77);
   cout << "\nCalling insertByPosition(4, 11) ---> "; list.insertByPosition(4, 11);
   cout << endl << endl;

   cout << "Calling insertByPosition(0, 8) ---> "; list.insertByPosition(0, 8);
   cout << "\nCalling insertByPosition(-5, 5) ---> "; list.insertByPosition(-5, 5);
   cout << "\nCalling insertByPosition(7, 35) ---> "; list.insertByPosition(7, 35);
   cout << "\nCalling insertByPosition(4, 15) ---> "; list.insertByPosition(4, 15);
   cout << "\nCalling insertByPosition(9, 38) ---> "; list.insertByPosition(9, 38);
   cout << "\nCalling insertByPosition(10, 70) ---> "; list.insertByPosition(10, 70);
   cout << "\nCalling insertByPosition(11, 70) ---> "; list.insertByPosition(11, 70);
   cout << "\nCalling insertByPosition(15, 80) ---> "; list.insertByPosition(15, 80);
   cout << "\n\nHere are the nodes now: ";
   list.displayList();

   return 0;
}
