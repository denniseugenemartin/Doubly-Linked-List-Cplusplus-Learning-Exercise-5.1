#include <iostream>
using namespace std;

// Node contains a data field and a pointer to a node which will point to the
// next Node added to the linked list.
struct Node
{
	int data;
	int error;
	Node* next;
	Node* previous;
		
};

// Node contain a head field, which will refer to the first element in the linked
// list. Tail will refer to the last element in the linked list.
class List
{
	Node* head;
	Node* tail;
	int size;

public:

	// When the list is created head and tail are both set to NULLand size to 0.
	// This indicates that there are no elements in the list.
	List()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}

	// This function will display the contents of the list in order.
	void printList()
	{
		// A pointer temp is set to the first element in the list.  A while loop is
		// initiated.  If the next property of the element being accessed is set to NULL
		// that indicates it is the last element in the list and the loop will exit.
		// Otherwise the loop prints the data field of the current Node and then follows
		// the next pointer to the next element in the list.
		if (size == 0)
		{
			cout << "List is empty.\n";
			return;
		}
		cout << "Current list :\n";
		Node* temp = head;
		while (temp->next != NULL)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}

		// This prints the data field of the last element in the list.
		cout << temp->data << endl;
	}

	// inserts a new node at a specified position in the linked list.	
	void insertNodeAt(int value, int index)
	{
		// create a temp pointer to a new node. set the new node's
		// data property to the passed value. 


		Node* temp = new Node;
		temp->data = value;

		// if this would be the first node in the list, increase size of list 
		// by one. Set previous/next pointers to NULL and set the new node as the head 
		// and tail of the list.
		if (size == 0)
		{
			++size;
			temp->next = NULL;
			head = temp;
			tail = temp;
			temp->previous = NULL;
			return;
		}

		// if the index is the first position in the linked list, set the new node's
		// next pointer to the previous head of the linked list and the
		// former head's previous pointer to the new node. 
		// Make the new node the head of the linked list and return.
		// The new node's previous field is set to NULL. size is increased by one.
		if (index == 0)
		{
			++size;
			temp->next = head;
			head->previous = temp;
			temp->previous = NULL;
			head = temp;
			return;
		}
		Node* current = head;
		// the current pointer starts and the head of the list and follows the next pointers
		// from node to node until it is at the appropriate position in the list. If the
		// current node is the tail of the list, then it set's the previous tail's next
		// pointer to the new node. It sets the new node's next pointer to NULL, sets it
		// to the tail pointer. The new node's previous pointer is set to the previous node and return.
		// If the user tries to set a node to a position
		// past the end of the list, it is simply added at the tail position. size is increased by one.
		for (int i = 0; i < index - 1; ++i)
		{
			if (current->next == NULL)
			{
				current->next = temp;
				temp->previous = current;
				tail = temp;
				temp->next = NULL;
				++size;
				return;
			}
			current = current->next;
		}

		// check to see if you are at the end of the list. if so place temp at the end of the list
		// and adjust pointers accordingly.
		if (current->next == NULL)
		{
			current->next = temp;
			temp->previous = current;
			tail = temp;
			temp->next = NULL;
			++size;
			return;
		}

		// if the loop ends before hitting the last node then the new node's next 
		// pointer is set to the current nodes next pointer location. The new node's
		// previous pointer is set to the current node's location. The next node after
		// the newly created node's previous pointer is moved to the new node.
		// it set's the new node's next pointer to the current node's next
		// pointer and then sets the current node's next pointer to the new node.
		// size is increased by one.
		temp->next = current->next;
		temp->previous = current;
		temp->next->previous = temp;
		current->next = temp;
		++size;

	}

	// calls insertNodeAt to last Node;
	void pushBack(int value)
	{
		insertNodeAt(value, size);
	}


	// calls insertNodeAt to the first node.
	void pushFront(int value)
	{
		insertNodeAt(value, 0);

	}

	// removes a Node at a specified position. 
	void removeNodeAt(int index)
	{
		Node* current = head;

		// if first Node is selected, the second node becomes the new head.
		// size is decreased by one.
		if (index == 0)
		{
			head = head->next;
			head->previous = NULL;
			current->next = NULL;
			delete current;
			size--;
			return;
		}

		// loop steps through list until it is in one position before requested position. 
		for (int i = 0; i < index - 1; ++i)
		{

			//if the next node is the tail, the current node is set to tail. Current pointer advances
			// one node forward. THe tail's next pointer is set to NULL. The current node is 
			// deleted. Size is decreased by one.
			if (current->next->next == NULL)
			{
				tail = current;
				current = current->next;
				tail->next = NULL;
				current->previous = NULL;
				delete current;
				--size;
				return;
			}
			current = current->next;
		}

		// the next pointer of the current node skips over the next node and is reassigned
		// to the following node. The next node's previous pointer  is pointed at the current node.
		// The skipped node is deleted. Size is decreased by one.
		Node* nodeToRemove = current->next;
		current->next = current->next->next;
		current->next->previous = current;
		nodeToRemove->next = NULL;
		nodeToRemove->previous = NULL;
		delete nodeToRemove;
		--size;
		return;
	}

	// calls removeNodeAt to the first node.
	void popFront()
	{
		removeNodeAt(0);
	}

	// calls removeNodeAt to the last node.
	void popBack()
	{
		removeNodeAt(size - 1);
	}


	// returns the data property from node at selected index position. 
	int getData(int index)
	{
		Node* current = head;

		// loop starts at the head and follows next pointers until it gets to the
		// selected index position. if index position would go out of bounds,
		// return a error message and -1.
		for (int i = 0; i < index; ++i)
		{
			if (current->next == NULL)
			{
				cout << "Invalid Node Position\n";
				return -1;
			}
			current = current->next;
		}
		return current->data;

	}

	// clears node from the list starting with the head node. size reset to 0. In each pass the 
	// previous/next pointers are set to NULL and the node is deleted.
	void clear()
	{
		size = 0;
		Node* current = head;
		while (current->next != NULL)
		{
			current = current->next;
			current->previous->next = NULL;
			delete current->previous;
			current->previous = NULL;

		}
		current->previous = NULL;
		delete current;
	}


	// returns current size of list.
	int getLength()
	{
		return size;
	}


	// this will reverse the order of the nodes in the list.
	void reverseNodes()
	{
		// if there are not nodes, tell the user so and return.
		if (size == 0)
		{
			cout << "No nodes present!\n";
			return;
		}

		// two pointers are created. endOfList points at the head of the list 
		// at the start.  This will end up as the tail of the list at the end.
		// the current pointer will move through the nodes as the loop goes on.
		Node* endOfNewList = head;
		Node* current = head;

		for (int i = 0; i < size - 1; ++i)
		{
			// move the element after the endOfNewList pointer
			// into the head position.
			head = endOfNewList->next;

			// the previous pointer of the node that the
			// current pointer is at will now point to the
			// head node.
			current->previous = head;

			// the next pointer of the endOfList will
			// pointed at the head of the list's old
			// next pointer.
			endOfNewList->next = head->next;

			// now the head's next pointer will be moved to the
			// current pointer's position.
			head->next = current;

			// The node to the right of the endOfTheNewList's
			// previous pointer is moved to the endOfNewList and 
			// the current pointer is moved to the head of the list.
			// This will not happen if we are at the end of the list.
			if (endOfNewList->next != NULL)
			{
				endOfNewList->next->previous = endOfNewList;
				current = head;
			}
		}

		// at the end of the loop ensure that the endOfNewList
		// has the  tail pointer and the head and tails previous
		// and next pointers are set to NULL.
		tail = endOfNewList;
		head->previous = NULL;
		tail->next = NULL;
	}

	// sets the value of a specific node's data property.
	void setNodeData(int value, int index)
	{

		// if user tries to index a position that is not in the list
		// tell them so and return.
		if (index > size - 1 || index < 0)
		{
			cout << "Invalid node position!\n";
			return;
		}
		Node* nodeToSetValue = head;

		// move through the list until you reach the index
		// position and change the data property to the value 
		// requested.
		for (int i = 0; i < index; ++i)
		{
			nodeToSetValue = nodeToSetValue->next;
		}

		nodeToSetValue->data = value;
	}
	int& operator [] (int index)
	{
		// if user tries to index a position that is not in the list
		// tell them so and return a reference to an unused error
		// property on the node.
		if (index > size - 1 || index < 0)
		{
			cout << "Invalid node position!\n";
			return head->error;
		}

		// move throught the list until you reach the
		// requested node and return a reference to
		// that node's data property.
		Node* nodeToReference = head;

		for (int i = 0; i < index; ++i)
		{
			nodeToReference = nodeToReference->next;
		}
		return nodeToReference->data;
	}

	// operator overload uses '=' to create a copy of the list on the right
	// side with same data.
	List& operator = (List& const listToBeCopied)
	{
		if (listToBeCopied.size == 0 || this == &listToBeCopied)
		{
			cout << "Cannot copy this list!\n";
			return listToBeCopied;
		}
	
		int value;
		
		// loop through the list using the pushback
		// function and getting the data from the listToBeCopied nodes
		// at the same position. 
		for (int i = 0; i < listToBeCopied.size; ++i)
		{
			value = listToBeCopied[i];
			pushBack(value);
		}
			
		return *this;
	}
};


int main()
{
	List list1;
	list1.pushBack(0);
	list1.pushBack(1);
	list1.pushBack(2);
	list1.pushBack(3);
	list1.pushBack(4);
	list1.reverseNodes();
	list1.printList();
	List list2;
	list2 = list1;
	cout << "list 2:\n";
	list2.printList();

	list1.pushBack(-1);
	list1.pushBack(-2);
	list1.pushFront(5);
	list1.printList();
	list1.clear();
	list1.printList();
	list1.pushBack(44);
	list1.printList();
	list1.pushFront(0);
	list1.setNodeData(1, 1);
	list1.printList();
	list1[1] = 99;
	list1[7] = 11;
	list1.printList();
	list2 = list2;
	
}