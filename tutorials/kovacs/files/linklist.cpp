#include"linklist.h"

// Implementation for an integer Singly Linked List
// Written by and (C) 1998 Daniel Kovacs

// Requires file "linklist.h"

// Dan's Domain Programming Repository
// http://personal.adesso.com/~dkovacs


// Insert an element at the head (start) of the linked list

void intLinkList::AddToHead(int el)
{
	head = new Node(el, head);
	if(!tail)
		tail = head;
}

// Add an element to the tail (end) of the linked list

void intLinkList::AddToTail(int el)
{
	if(tail) {
		tail->next = new Node(el);
		tail = tail->next;
	}
	else head = tail = new Node(el);
}

// Remove an element from start of Linked List

int intLinkList::RemoveFromHead()
{
	if(head) {
		el = head->info;
		tmp = head;
		if(head == tail)
			head = tail = 0;
		else
			head = head->next;
		delete tmp;
		return el;
	}
	else
		return 0;
}

// Remove an element from the end of the linked list

int intLinkList::RemoveFromTail()
{
	if(tail) {
		el = tail->info;
		if(head == tail)
		{
			delete head;
			head = tail = 0;
		}
		else
		{
			for(tmp = head; tmp->next != tail; tmp = tmp->next);
			delete tail;
			tail = tmp;
			tail->next = 0;
		}
		return el;
	}
	else
		return 0;
}

// Search for an element in the linked list
// Will return the element if found, otherwise it returns 0

int intLinkList::Search(int e)
{
	tmp = head;
	while(tmp->next != tail)
	{
		if(tail->info == e)
			return e;
		if(tmp->info == e)
			return e;
		else
			tmp = tmp->next;
	}
	return 0;
}		
