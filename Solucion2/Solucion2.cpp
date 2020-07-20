#include "Solucion2.h"

Solucion2::Solucion2(LinkedList* linkedList) {
    list = linkedList;
    maxHeap = new MaxHeap();
    references = new std::map<pair<int, int>, reference>();
}

Solucion2::~Solucion2() {
    delete references;
    delete maxHeap;
    if (list != nullptr)
        delete list;    
}

void Solucion2::compress() {
    loadData();
    // printCompress();

    auto max = maxHeap->getMax();
    long count = 0;
    while (max.first > 1) {
        count++;
        if(count == 46)
            int aaaa = 1234;
        cout << "count=" << count << ", freq=" << max.first << ", pair={" << max.second.first << ", " << max.second.second << "}, replacement = " << replacement << endl;
        if (max.second == make_pair(26, 2)) // 26, 2 f 18 y mata uno de 26,26 f 15. it 92
            int aaaa = 1234;
        auto ref = references->at(max.second);
        auto nodo = ref.first;
        compressPairMejora3(nodo, *(ref.heapIndex),this->replacement);
        this->replacement++;
        maxHeap->extractMax();
        max = maxHeap->getMax();
    }
}

void Solucion2::compressPair(nodo* curNode, int index, int replacement) {    
    nodo* nextOcurr;
    int x = curNode->n;
    int y = curNode->next->n;
    do {        
        nextOcurr = nullptr;
        if (curNode->nextOcurr != nullptr) {
            if (curNode->nextOcurr != curNode->next) {
                nextOcurr = curNode->nextOcurr;
            } else {
                nextOcurr = curNode->nextOcurr->nextOcurr;
            }            
        }
        
        // borrado y update
        if (curNode->prev->n > -1) {
            auto del_prev_pair = make_pair(curNode->prev->n, curNode->n);
            maxHeap->updateFrequency(del_prev_pair, -1);
            deleteFromMap(del_prev_pair, curNode->prev);
        }
        if (curNode->next->n > -1 && curNode->next->next != nullptr) {
            auto del_next_pair = make_pair(curNode->next->n, curNode->next->next->n);
            maxHeap->updateFrequency(del_next_pair, -1);
            deleteFromMap(del_next_pair, curNode->next);
        }
        
        nodo* nodeToDelete = curNode->next;                
        list->popAt(nodeToDelete);      
        // insertar nuevos pares
        curNode->n = replacement;
        if (curNode->prev != nullptr && curNode->prev->n != -2) {
            auto new_prev_pair = make_pair(curNode->prev->n, curNode->n);
            maxHeap->insert(new_prev_pair);
            updateReference(new_prev_pair, curNode->prev);
        }

        if (curNode->next->n != -2) { 
            auto new_next_pair = make_pair(curNode->n, curNode->next->n);
            maxHeap->insert(new_next_pair);        
            updateReference(new_next_pair, curNode);
        }

        curNode = nextOcurr;
    } while (curNode != nullptr);
    references->erase(make_pair(x, y)); 
}


void Solucion2::compressPairMejora3(nodo* curNode, int index, int replacement) {    
    nodo* nextOcurr; 
    auto pairRef = make_pair(curNode->n, curNode->next->n);    
    do {        
        int n_prev = -1, n = curNode->n, n_next = curNode->next->n, n_next_next = -1;
        // eliminar pares
        if (curNode->prev->n > -1) {
            n_prev = curNode->prev->n;
            auto del_prev_pair = make_pair(n_prev, n);
            maxHeap->updateFrequency(del_prev_pair, -1);
            deleteFromMap(del_prev_pair, curNode->prev);
        }

        if (curNode->next->next->n > -1) {
            n_next_next = curNode->next->next->n;
            if (pairRef != make_pair(n_next, n_next_next)) {
                auto del_next_pair = make_pair(n_next, n_next_next);
                maxHeap->updateFrequency(del_next_pair, -1);
                deleteFromMap(del_next_pair, curNode->next);
            }
        }

        // sacar segundo item de la ll
        nodo* nodeToDelete = curNode->next;                
        list->popAt(nodeToDelete);
        
        // insertar nuevos pares
        // reemplazo par
        curNode->n = replacement;
        // guardo puntero a siguiente ocurrencia antes de actualizar los punteros a la siguiente ocurrencia
        nextOcurr = curNode->nextOcurr;
        fixOccPtr(curNode);
        n = curNode->n;
        if (n_prev > -1) {            
            auto new_prev_pair = make_pair(n_prev, n);
            maxHeap->insert(new_prev_pair);
            updateReference(new_prev_pair, curNode->prev);
        }

        if (n_next_next > -1) { 
            auto new_next_pair = make_pair(n, n_next_next);
            maxHeap->insert(new_next_pair);        
            updateReference(new_next_pair, curNode);
        }
        curNode = nextOcurr;
    } while (curNode != nullptr);
    references->erase(pairRef); 
    delete nextOcurr;
}

void Solucion2::updateReference(std::pair<int, int> pair, nodo* nodo) {
    auto itRef = references->find(pair);
    if (itRef == references->end()) {
        // no existe
        struct reference ref;
        ref.first = nodo;
        ref.last = nodo;
        ref.heapIndex = maxHeap->getIndexPtr(pair);
        references->insert(make_pair(pair, ref));
    } else {
        // existe
        nodo->prevOcurr = itRef->second.last;
        itRef->second.last->nextOcurr = nodo;
        itRef->second.last = nodo;    
        itRef->second.heapIndex = maxHeap->getIndexPtr(pair);        
    }
}

void Solucion2::loadData() {
    auto it = list->begin(); 
    auto last = it.end();
    auto nodo = it.nodo();
    last = last->prev;
    
    while (nodo != last) {
        auto next = nodo->next; 
        auto pair = make_pair(nodo->n, next->n);       
        maxHeap->insert(pair);
        updateReference(pair, nodo);
        nodo = next;
    }   
}

void Solucion2::deleteFromMap(std::pair<int, int> pair, nodo* nodo) {    
    auto it = references->find(pair);
    if (it != references->end()) {
        if (it->second.first == nodo && it->second.last == nodo) {
            references->erase(it);
        } else if (it->second.last == nodo) {
            it->second.last = nodo->prevOcurr;
        } else if (it->second.first == nodo){
            it->second.first = nodo->nextOcurr;
        }        
        fixOccPtr(nodo);
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