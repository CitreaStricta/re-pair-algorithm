
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "iterator.h"

class LinkedList
{
	private:
		int mysize;
	public:
		struct nodo *head;
		struct nodo *tail;
		LinkedList();
		~LinkedList();
		void insertAtTail(int n);
		void insertAt(int n, nodo *k);
		void popAt(nodo *k);
		nodo* getPtrAt0();
		int at(int pos);
		int size();
		Iterator begin();
};

#endif