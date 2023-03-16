// A class template for holding a linked list.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

using namespace std;

//Definition of the Node structure for the list
template <class T>
struct Node
{
   T value;     // The value in this node
   Node *next;  // To point to the next node
};

template <class T>
class LinkedList
{
private:
    Node<T> *head;   // List head pointer

public:
    // Constructor
    LinkedList()
    { head = nullptr; }

    //deep copy copy constructor
    LinkedList(const LinkedList &l)
    {
        head = new Node<T>;
        head = l.head;
    }

    // Destructor
    ~LinkedList();

    // Linked list operations
    void insertNode(T);
    void deleteNode(T);
    void displayList() const;
    void deleteByPosition(int position);
    void insertByPosition(int position, T newValue);
    int search(T searchValue) const;
    int countNodes() const;

};

//**************************************************
// insert by position fnction attempts to insert a *
// new value at the specified position             *
//   *
//**************************************************
template <class T>
void LinkedList<T>::insertByPosition(int position, T newValue)
{
    Node<T> *newNode;					// A new node
    Node<T> *nodePtr;					// To traverse the list
    Node<T> *previousNode = nullptr;	// The previous node
    int localPos;                       // to keep track of the index in the list

    // Allocate a new node and store newValue there.
    newNode = new Node<T>;
    newNode->value = newValue;

    string errorString = "Error in insertByPosition function, pos causes unsorted linked list.\n";


    if (!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else  // Otherwise, insert newNode
    {
        // Position nodePtr at the head of list.
        nodePtr = head;

        // Initialize previousNode to nullptr.
        previousNode = nullptr;

        // Skip all nodes whose value is less than newValue.
        while (nodePtr != nullptr && nodePtr->value < newValue)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
            localPos++; // to keep track of the index
        }

        // If the new node is to be the 1st in the list,
        // insert it before all other nodes.
        if (previousNode == nullptr && localPos <= 0)
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        else if (position >= countNodes() && nodePtr == nullptr)
        {
            previousNode->next = newNode;
            newNode->next = nullptr;
        }
        else if (localPos != position)
        {
            throw errorString;
        }
        else  // Otherwise insert after the previous node.
        {
            previousNode->next = newNode;
            newNode->next = nodePtr;
        }
   }
}

//**************************************************
// search returns the position of                  *
// searchValue in the linked list                  *
// function returns -1 if searchValue isn't found  *
//**************************************************
template <class T>
int LinkedList<T>::search(T searchValue) const
{
    int position;   // stores the index to return

    Node<T> *nodePtr;  // To move through the list
    nodePtr = head;

    //traverse through the list and compare searchValue
    while (nodePtr)
    {
        if (nodePtr->value == searchValue)
        {
            return position;
        }
        //move the node to next
        nodePtr = nodePtr->next;
        //increment pos
        position++;
    }
    return -1;
}

//**************************************************
// countNodes returns the number of nodes          *
// in the linked list                              *
//**************************************************
template <class T>
int LinkedList<T>::countNodes() const
{
    Node<T> *nodePtr;  // To move through the list
    nodePtr = head;

    int numberOfNodes;

    while (nodePtr)
    {
        //move the node to next
        nodePtr = nodePtr->next;
        //count it
        numberOfNodes++;
    }

    return numberOfNodes;
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
//**************************************************

template <class T>
void LinkedList<T>::displayList() const
{
   Node<T> *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr points to a node, traverse
   // the list.
   while (nodePtr)
   {
      // Display the value in this node.
      cout << nodePtr->value << " ";

      // Move to the next node.
      nodePtr = nodePtr->next;
   }

   cout << endl;
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
// New node is added in its proper sorted location *
// in the list                                     *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
   Node<T> *newNode;					// A new node
   Node<T> *nodePtr;					// To traverse the list
   Node<T> *previousNode = nullptr;	// The previous node

   // Allocate a new node and store newValue there.
   newNode = new Node<T>;
   newNode->value = newValue;

   // If there are no nodes in the list
   // make newNode the first node
   if (!head)
   {
      head = newNode;
      newNode->next = nullptr;
   }
   else  // Otherwise, insert newNode
   {
      // Position nodePtr at the head of list.
      nodePtr = head;

      // Initialize previousNode to nullptr.
      previousNode = nullptr;

      // Skip all nodes whose value is less than newValue.
      while (nodePtr != nullptr && nodePtr->value < newValue)
      {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If the new node is to be the 1st in the list,
      // insert it before all other nodes.
      if (previousNode == nullptr)
      {
         head = newNode;
         newNode->next = nodePtr;
      }
      else  // Otherwise insert after the previous node.
      {
         previousNode->next = newNode;
         newNode->next = nodePtr;
      }
   }
}

//*****************************************************
// The deleteNode function searches for a node        *
// with searchValue as its value. The node, if found, *
// is deleted from the list and from memory.          *
//*****************************************************

template <class T>
void LinkedList<T>::deleteNode(T searchValue)
{
   Node<T> *nodePtr;       // To traverse the list
   Node<T> *previousNode;  // To point to the previous node

   // If the list is empty, do nothing.
   if (!head)
      return;

   // Determine if the first node is the one.
   if (head->value == searchValue)
   {
      nodePtr = head->next;
      delete head;
      head = nodePtr;
   }
   else
   {
      // Initialize nodePtr to head of list
      nodePtr = head;

      // Skip all nodes whose value member is
      // not equal to num.
      while (nodePtr != nullptr && nodePtr->value != searchValue)
      {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If nodePtr is not at the end of the list,
      // link the previous node to the node after
      // nodePtr, then delete nodePtr.
      if (nodePtr)
      {
         previousNode->next = nodePtr->next;
         delete nodePtr;
      }
   }
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
   Node<T> *nodePtr;   // To traverse the list
   Node<T> *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != nullptr)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}
#endif
