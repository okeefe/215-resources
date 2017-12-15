#include"hashtable.h"

// Implementation for an integer Hash Table
// Written by and (C) 1998 Daniel Kovacs

// Uses:
//      LinkList.h
//      LinkList.cpp

//      Hashtable.h

// Dan's Domain Programming Repository
// http://personal.adesso.com/~dkovacs

// Compute the Hash Function and "Hash" element into table
	
void HashTable::Hash(int el)
{
		table[el%10].AddToTail(el);
		keys++;
}

// Simple Search Function
// Returns the element searched for if found, 0 otherwise

int HashTable::Search(int el)
{
		return(table[el%10].Search(el));
}

// Returns the total number of keys in the table

int HashTable::Total()
{
	return(keys);
}

// Print the hash table (for demonstration purposes

void HashTable::PrintHashTable()
{
	int i = 0, e;
	while(i < 10)
	{
		cout << i <<": ";
		e = table[i].RemoveFromHead();
		while(e != 0)
		{
			cout << e << " -> ";
			e = table[i].RemoveFromHead();
		}
		cout << "|" << endl;
		i++;
	}
}
