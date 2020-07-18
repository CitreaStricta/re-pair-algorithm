#include "./LinkedList/nodo.h"
#include "./LinkedList/LinkedList.h"
#include "MaxHeap.h"

struct helper {
    nodo *first;
    nodo *last;
    int heapIndex;
};

LinkedList *compress(LinkedList *list) {
    auto maxHeap = new MaxHeap();
    auto map = new std::map<pair<int, int>, helper *>();
    auto it = list->begin(); 
    auto last = it.end();
    auto nodo = it.nodo();
    last = last->prev->prev;
    while (nodo != last) {
        auto nodo1 = nodo->next; 
        auto pair = make_pair(nodo->n, nodo1->n);
        maxHeap->insert(pair);
    }    
}