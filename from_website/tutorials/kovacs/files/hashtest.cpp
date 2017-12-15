#include<hashtable.h>

// Class for an integer Hash Table
// Written by and (C) 1998 Daniel Kovacs

// Uses:
//      LinkList.h
//      LinkList.cpp

//      HashTable.h
//      HashTable.cpp

// Dan's Domain Programming Repository
// http://personal.adesso.com/~dkovacs

// Enter a number of keys into the hash table, and then display
// the structure of the table.

void main()
{
	HashTable myHashTable;
	
	int el;
	
	cout << "Enter some values into the table:" << endl;
	cin >> el;
	
	while(el!=0)
	{
		myHashTable.Hash(el);
		cin >> el;
	}
	
	myHashTable.PrintHashTable();
}
