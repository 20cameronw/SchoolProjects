/**
CSC 232 - SU22
HW 3: Doubly linked list implementation of a stack
7/15/2022
Cameron Weston
Jacob Rich
*/

#include <iostream>
#include <cassert>

using namespace std;

template <class T>
struct StackNode
{
    T data;                // The data stored in a node
    StackNode<T>* top;     // Link to node on top of this node
    StackNode<T>* bottom;  // Link to node below this node
};

template <class T>
class Stack
{
private:
    StackNode<T>* head; // Pointer to the node at the top of the stack
    void copyStack(const Stack<T>& other);
public:
    Stack(); //Default Constructor
    ~Stack(); //Destructor
    void push(T newValue);
    bool isEmpty();
    void pop();
    T top();
    Stack(const Stack<T>& other);
    const Stack<T>& operator = (const Stack<T>& S);

    void displayStack(); // Prints the data stored in the stack. Useful for testing

}; //stack

//Default constructor for creating an initially empty stack
template <class T>
Stack<T>::Stack()
{
    head = nullptr;
}

template <class T>
void Stack<T>::push(T newValue)
{
    StackNode<T>* newNode; //Pointer to new node

    // Create a new node to store newValue
    newNode = new StackNode<T>;
    newNode->data = newValue;
    newNode->top = nullptr;
    newNode->bottom = head; //This works even if head is nullptr

    if (head == nullptr) // If the stack is empty
    {
        head = newNode;
    }
    else
    {
        head->top = newNode;
        head = newNode;
    }

}//push

template <class T>
void Stack<T>::displayStack()
{
    StackNode<T>* p; // Pointer to traverse stack

    p = head;
    while (p != nullptr)
    {
        cout << p->data << " ";
        p = p->bottom;
    }
    cout << endl;
} // end displayStack

template <class T>
bool Stack<T>::isEmpty()
{
    return (head == nullptr);
}

template <class T>
T Stack<T>::top()
{
    assert(head != nullptr);

    return head->data;
} // end top

template <class T>
void Stack<T>::pop()
{
    StackNode<T>* p; // Pointer to traverse stack
    if (!isEmpty())
    {
        p = head;
        head = head->bottom;
        delete p;
    }
    else
    {
        cout << "Cannot remove from an empty stack." << endl;
    }
} // end pop

template <class T>
Stack<T>::~Stack()
{
    StackNode<T>* p; // Pointer to traverse stack

    while (head != nullptr)
    {
        p = head;
        head = head->bottom;
        delete p;
    }
}

template <class T>
void Stack<T>::copyStack(const Stack<T>& other)
{
    StackNode<T>* nodePtr = NULL;
    StackNode<T>* nextNode = NULL;
    StackNode<T>* bottom = NULL;

    if (head != nullptr)
        this->Stack<T>::~Stack();

    if (other.head == 0)
    {
        head = 0;
    }
    else
    {
        head = new StackNode<T>;
        head->data = other.head->data;

        nodePtr = head;
        nextNode = other.head->bottom;

        while (nextNode)
        {
        nodePtr->bottom = new StackNode<T>;
        nodePtr = nodePtr->bottom;
        nodePtr->data = nextNode->data;

        nextNode = nextNode->bottom;
        }
    }
}

template <class T>
Stack<T>::Stack(const Stack& other)
{
    head = nullptr;
    copyStack(other);
}

template <class T>
const Stack<T>& Stack<T>::operator= (const Stack<T>& S)
{
    if (this != &S) //avoid self-copy
        copyStack(S);

    return *this;
}

int main()
{
    Stack<int> s1;

    for (int i = 1; i <= 5; i++)
        s1.push(i);

    s1.displayStack();

    while (!s1.isEmpty())
    {
        int value = s1.top();
        cout << value << endl;
        s1.pop();
    }

    Stack<string> s2;
    s2.push("Mark");
    s2.push("John");
    s2.push("Eric");
    cout << "\nContents of s2: ";
    s2.displayStack();

    //Testing the copy Constructor
    cout << "\nTesting the copy constructor" << endl;
    Stack<string> s3(s2);
    cout << "Contents of s3: ";
    s3.displayStack();

    //Testing the overloaded assignment operator
    cout << "\nTesting the overloaded assignment operator" << endl;
    Stack<string> s4;
    s4 = s2;
    cout << "\nContents of s4: ";
    s4.displayStack();
    s4.pop();
    s4.pop();
    s4.push("David");
    cout << "\nContents of s4 after two pops and one push: ";
    s4.displayStack();

    return 0;

}
