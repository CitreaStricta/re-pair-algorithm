#include "solDos.h"

solDos::solDos()
{
    maxHeap = new MaxHeap();
    _map = new map<pair<int, int>, str>();
}

solDos::~solDos(){}

void solDos::Compress(LinkedList *listD)
{
    auto it = listD->begin();
    auto last = it.end();
    last = last->prev->prev;
    while (it.nodo() != last)
    {
        auto nodo1 = it.nodo()->next; 
        auto pair = make_pair(it.nodo()->n, it.nodo()->next->n);
        maxHeap->insert(pair);
        it++;
    }
    return;
}