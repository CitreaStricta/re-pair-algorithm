#include "Solucion2.h"

Solucion2::Solucion2(LinkedList* linkedList) {
    list = linkedList;
    maxHeap = new MaxHeap();
    references = new std::map<pair<int, int>, reference>();
    symbols.push_back(27);
}

Solucion2::~Solucion2() {
    delete references;
    delete maxHeap;
    delete list;    
}

void Solucion2::compress() {
    loadData();
    auto max = maxHeap->extractMax();
    while (max.first > 1) {
        auto ref = references->at(max.second);
        auto nodo = ref.first;
        compressPair(nodo, this->replacement);
        this->replacement++;
        max = maxHeap->extractMax();
    }    
}

void Solucion2::compressPair(nodo* curNode, int replacement) {    
    references->erase(make_pair(curNode->n, curNode->next->n)); 
    do {
        // borrado y update
        if (curNode->prev != nullptr) {
            auto del_prev_pair = make_pair(curNode->prev->n, curNode->n);
            maxHeap->updateFrequency(del_prev_pair, -1);
            deleteFromMap(del_prev_pair, curNode->prev);
        }
        if (curNode->next != nullptr && curNode->next->next != nullptr) {
            auto del_next_pair = make_pair(curNode->next->n, curNode->next->next->n);
            maxHeap->updateFrequency(del_next_pair, -1);        
            deleteFromMap(del_next_pair, curNode->next);
        }
        nodo* nodeToDelete = curNode->next;        
        list->popAt(nodeToDelete);       
        // insertar nuevos pares
        curNode->n = replacement;
        if (curNode->prev != nullptr) {
            auto new_prev_pair = make_pair(curNode->prev->n, curNode->n);
            maxHeap->insert(new_prev_pair);
            updateReference(new_prev_pair, curNode->prev);
        }
        if (curNode->next != nullptr && curNode->next->next != nullptr) {
            auto new_next_pair = make_pair(curNode->n, curNode->next->n);
            maxHeap->insert(new_next_pair);        
            updateReference(new_next_pair, curNode);
        }
        curNode = curNode->nextOcurr;
    } while (curNode != nullptr);
}

void Solucion2::updateReference(std::pair<int, int> pair, nodo* nodo) {
    auto itRef = references->find(pair);
    if (itRef == references->end()) {
        // no existe
        struct reference ref;
        ref.first = nodo;
        ref.last = nodo;
        ref.heapIndex = maxHeap->getIndex(pair);
        references->insert(make_pair(pair, ref));
    } else {
        // existe
        itRef->second.last = nodo;
        itRef->second.heapIndex = maxHeap->getIndex(pair);
    }
}

void Solucion2::loadData() {
    auto it = list->begin(); 
    auto last = it.end();
    auto nodo = it.nodo();
    last = last->prev->prev;    
    
    while (nodo != last) {
        auto nodo1 = nodo->next; 
        auto pair = make_pair(nodo->n, nodo1->n);
        maxHeap->insert(pair);
        updateReference(pair, nodo);
        nodo = nodo1;
    }   
}

void Solucion2::deleteFromMap(std::pair<int, int> pair, nodo* nodo) {
    auto it = references->find(pair);
    if (it != references->end()) {
        if (it->second.first == nodo && it->second.last == nodo) {
            references->erase(it);
        } else if (it->second.last == nodo) {
            it->second.last = nodo;
        } else {
            it->second.first = nodo;
        }
        it->second.heapIndex = maxHeap->getIndex(pair);
    }
}

void Solucion2::printCompress() {
    int aux = list->at(0);
    int i = 1;
    while(aux > 0)
    {
        cout << aux << " ";
        aux = list->at(i++);
    }
    cout << endl;
}