#pragma once
#include <iostream>
using namespace std;
#include "Nodepriority.h"


template <typename T>
class PriorityQueue
{
private:
	Nodepriority<T>* Head;
	int count;
public:
	//Constructor
	PriorityQueue()
	{
		Head = NULL; //Amr Aho
	}

	//Function that enqueues the elemtents sorted according to the key
	bool enqueue(const T& newEntry, const int& newKey)
	{
		//Creating the new node to be inserted 
		Nodepriority<T>* temp = new Nodepriority<T>(newEntry, newKey);
		Nodepriority<T>* ptr;

		//If the entry is in the first place or the list is empty
		if (Head == NULL || (temp->getKey() < Head->getKey()))
		{
			temp->setNext(Head);
			Head = temp;
		}
		//General Case
		else
		{
			ptr = Head;
			while (ptr->getNext() != NULL && ptr->getNext()->getKey() <= temp->getKey())
				ptr = ptr->getNext();

			temp->setNext(ptr->getNext());
			ptr->setNext(temp);
		}
		count++;
		return true;
	}

	//Function the takes out elements out of the queue
	bool dequeue(T& temp)//Node<T>*& temp
	{
		if (isEmpty())
			return false;

		temp = Head->getData();
		Head = Head->getNext();
		count--;
		return true;

	}
	int getcount() { return count; }
	//Function the checks the first element.
	bool peek(T& temp)
	{
		if (isEmpty())
			return false;

		temp = Head->getData();
		return true;

	}

	//Function that checks whether the queue is empty or not
	bool isEmpty()
	{
		return (Head == NULL);
	}

	void print() const
	{
		Nodepriority<T>* ptr = Head;
		while (ptr)
		{
			cout << ptr->getKey() << " ";// depends if we need to print the key
			cout << ptr->getData() << " ";
			ptr = ptr->getNext();
		}
		cout << endl;
	}

};