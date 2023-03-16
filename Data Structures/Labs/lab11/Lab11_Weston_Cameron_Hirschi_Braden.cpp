/**
 Cameron Weston
 Lab 11 - Recursive Linked Lists
 7/26/2022
*/

#include <iostream>

using namespace std;

// Declare a structure for the list
struct ListNode
{
    int value;
    ListNode *next;
};

class LinkedListRec
{
private:
    ListNode *head;    // List head pointer
    void destroyList(); // recursive function to destroy the linked list
    void displayList(const ListNode*) const; //recursive function to display the info in the list
    int countNodes(ListNode *nodePtr) const; //recursive function to count number of nodes in the list
    bool search(ListNode *nodePtr, int value) const;  // recursive function to check if a value exists in the list
    void printReverse(const ListNode*) const; //recursive function to display the list in reverse order
    void replace(ListNode *nodePtr, int oldValue, int newValue); //recursive function to replace every occurrence of old with new

public:
   // Constructor
   LinkedListRec()
      { head = nullptr; }

    bool isEmpty() const;

    void addFirst(int); //add new node with specified data at the head

    void displayList() const; //wrapper function to display the info in the list

    int countNodes() const; //wrapper function to count number of nodes

    bool search(int) const; //wrapper function to check for an int

    void printReverse() const; //wrapper function to display contents backwards

    void replace(int oldValue, int newValue); //wrapper function to replace all old with new

   // Destructor
   ~LinkedListRec();
};

//wrapper function to replace all of the old values with new value
void LinkedListRec::replace(int oldValue, int newValue)
{
    replace(head, oldValue, newValue);
}

//recursive helper function to replace all of the old values with new value
void LinkedListRec::replace(ListNode *nodePtr, int oldValue, int newValue)
{
    if (nodePtr == nullptr)
        return;
    else if (nodePtr->value == oldValue)
    {
        nodePtr->value = newValue;
        replace(nodePtr->next, oldValue, newValue);
    }
    else
    {
        replace(nodePtr->next, oldValue, newValue);
    }
}

//wrapper function to print contents in reverse order
void LinkedListRec::printReverse() const
{
    printReverse(head);
}

//prints the contents in reverse order
void LinkedListRec::printReverse(const ListNode* nodePtr) const
{
    if (nodePtr != nullptr)
    {
        printReverse(nodePtr->next);
        cout << nodePtr->value << " ";
    }
}

//returns true if the value passed to it is in the linked list
bool LinkedListRec::search(int value) const
{
    return search(head, value);
}

//recursively search for the value in the list
bool LinkedListRec::search(ListNode *nodePtr, int value) const
{
    if (nodePtr == nullptr)
        return false;
    else if (nodePtr->value == value)
        return true;
    else
    {
        return search(nodePtr->next, value);
    }
}

//returns true if list is empty
bool LinkedListRec::isEmpty() const
{
   return head == nullptr;
}

//destructor
LinkedListRec::~LinkedListRec()
{
    destroyList();
}

void LinkedListRec::destroyList()
{
    if (head == nullptr) //case list is empty
        return;
    else if (head->next == nullptr) //case list has only one node
        delete head;
    else //case list has more than one node
    {
        ListNode * temp;
        temp = head;
        head = head -> next;
        delete temp;
        destroyList();
    }
}//destroyList()

void LinkedListRec::addFirst(int data)
{
  ListNode * newNode = new ListNode;
  newNode -> value = data;
  newNode -> next = head;
  head = newNode;
}

void LinkedListRec::displayList() const
{
   displayList(head);
}

//recursively display the data in the list
void LinkedListRec::displayList(const ListNode* nodePtr) const
{
    if (nodePtr == nullptr)
        return;
    else
    {
        cout << nodePtr->value << " "; //display data stored in current node
        displayList(nodePtr->next); //call function recursively on remaining nodes
    }
}

int LinkedListRec::countNodes() const
{
    return countNodes(head);
}

int LinkedListRec::countNodes(ListNode *nodePtr) const
{
   if (nodePtr == nullptr)
      return 0;
   else
      return 1 + countNodes(nodePtr->next);
}

int main()
{
    LinkedListRec myList;
    for (int i = 1; i<= 5; i++)
        myList.addFirst(i);
    myList.displayList();

    cout <<"\nPrinting the list in reverse: ";
    myList.printReverse();
    cout << endl;

    cout << "\nNumber of nodes in the list is " << myList.countNodes() << endl;

    cout << "\nIs the value 3 in the list? " << myList.search(3) << endl;
    cout << "Is the value 7 in the list? " << myList.search(7) << endl;

    cout << "\nReplacing 2 by 4";
    myList.replace(2, 4);
    cout << "\nReplacing 4 by 25";
    myList.replace(4, 25);
    cout <<"\nThe list now is: ";
    myList.displayList();
}
