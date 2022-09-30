#include "LinkedList.h"
template< class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
} // end default constructor

//template< class ItemType>
/*ItemType LinkedList<ItemType>::getEntry(int position) const
//throw(PrecondViolatedExcep)                  // Able to ininsert variable is an indicator of the poistion
{
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
	else
	{
		string message = "getEntry() called with an empty list or ";
		message = message + "invalid position.";
		//throw(PrecondViolatedExcep(message));
	} // end if
} // end getEntry
*/
template< class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const        // Menna I have Modified in this func 
{
	// Debugging check of precondition 
	bool abletoinsert = ((position >= 1) && (position <= itemCount));
	Node<ItemType>* curPtr = headPtr;
	// Count from the beginning of the chain 
	if (abletoinsert)
	{

		for (int skip = 1; skip < position; skip++)
			curPtr = curPtr->getNext();

		return curPtr;
	}
}
template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
}
// end getNodeAt
template< class ItemType>
bool LinkedList<ItemType>::insert(int newPosition,
	const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) &&
		(newPosition <= itemCount + 1);
	if (ableToInsert)
	{
		// Create a new node containing the new entry
		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
		// Attach new node to chain 
		if (newPosition == 1)
		{
			// Insert new node at beginning of chain 
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else
		{
			// Find node that will be before new node 
			Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
			// Insert new node after node to which prevPtr points 
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		} // end if 
		itemCount++; // Increase count of entries 
	} // end if 
	return ableToInsert;
} // end insert
template< class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<ItemType>* curPtr = nullptr;
		if (position == 1)
		{
			// Remove the first node in the chain 
			curPtr = headPtr; // Save pointer to node 
			headPtr = headPtr->getNext();
		}
		else
		{
			// Find node that is before the one to delete 
			Node<ItemType>* prevPtr = getNodeAt(position - 1);
			// Point to node to delete 
			curPtr = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the 
			 // prior node with the one after 
			prevPtr->setNext(curPtr->getNext());
		} // end if 
	   // Return node to system 
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		itemCount--; // Decrease count of entries 
	} // end if 
	return ableToRemove;
} // end remove 
template< class ItemType>
void LinkedList<ItemType>::clear()
{
	while (!isEmpty())
		remove(1);
} // end clear 
template< class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
} // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	if (itemCount == 0)
		return true;
	else return false;
}
