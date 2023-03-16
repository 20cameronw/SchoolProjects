// This program demonstrates the linked list template.
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
   // Define a LinkedList object.
   LinkedList<int> list;

   // Display the values in the list.
   cout << "Here are the initial values:\n";
   list.displayList();
   cout << endl;


   // Insert few values
   list.insertNode(10);
   list.insertNode(15);
   list.insertNode(5);
   list.insertNode(25);
   list.insertNode(20);
   list.insertNode(50);
   list.insertNode(40);
   list.insertNode(30);
   // Display the values in the list.
   cout << "Here are the nodes now.\n";
   list.displayList();
   cout << endl;

   // Delete few nodes.
   cout << "Now deleting the last node.\n";
   list.deleteNode(25);
   cout << "Now deleting a node in the middle.\n";
   list.deleteNode(30);
   cout << "Now deleting the first node.\n";
   list.deleteNode(5);

   // Display the values in the list.
   cout << "Here are the nodes left.\n";
   list.displayList();
   return 0;
}
