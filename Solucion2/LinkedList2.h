#include "iterator2.h"

class LinkedList2
{
private:
		int mysize;
	public:
		struct nodo2 *head;
		struct nodo2 *tail;
		LinkedList2();
		~LinkedList2();
		void insertAtTail(int n);
		void insertAt(int n, nodo2 *k);
		void popAt(nodo2 *k);
		nodo2* getPtrAt0();
		int at(int pos);
		int size();
		Iterator2 begin();
};

