

#include <iostream>
#include "DynamicIntStack.h"
using namespace std;

template <class T>
//Constructor

DynamicIntStack<T> ::DynamicIntStack()
{
	top=NULL;
}

template <class T>
T* DynamicIntStack<T>::GetTopPointer()
{
	return top;
}

//Push back elements to the stack

template <class T>
void DynamicIntStack<T>::push(T stackNode)
{
	IntStackNode *newNode;

    newNode = new IntStackNode;
    newNode->cell = stackNode;

    if(isEmpty())
    {
        top = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }
}
//Pop up elements from the stack
template <class T>
void DynamicIntStack<T>::pop() 
{
	IntStackNode *temp;

    if(isEmpty())
    {
        cout<<"Stack is empty!\n";
    }

    else
    {
        //elmt = top->cell;
        temp = top->next;
        delete top;
        top= temp;
        
    }
}

//If the stack is empty check function
template <class T>
bool DynamicIntStack<T>::isEmpty()
{
	bool status;

	if(top==NULL)
		status=true;

	else 
		status=false;

	return status;
}

template <class T>
void DynamicIntStack<T>::clear() {
	
	while (!isEmpty()) {
		pop();
	}
}
