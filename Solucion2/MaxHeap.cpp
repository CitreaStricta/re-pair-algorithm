#include "MaxHeap.h"

MaxHeap::MaxHeap() {
    vect = new vector<pair<int, pair<int, int>>>();
    posiciones = new map<pair<int, int>, int>();
}

MaxHeap::~MaxHeap() {
    delete vect;
    delete posiciones;
}

int MaxHeap::getIndex(std::pair<int, int> pair) {
    auto it = posiciones->find(pair);
    int index = 0;
    if (it != posiciones->end())
        index = it->second;
    else
        index = -1;
    return index;
}

void MaxHeap::updateIndex(std::pair<int, int> pair, int newIndex) {
    auto it = posiciones->find(pair);
    if (it != posiciones->end())
        it->second = newIndex;
}

void MaxHeap::swap(int i1, int i2) {
    auto aux = vect->at(i1);
    vect->at(i1) = vect->at(i2);
    vect->at(i2) = aux;
    auto swappedPair = aux.second;    
    updateIndex(swappedPair, i2);
    swappedPair = vect->at(i1).second;
    updateIndex(swappedPair, i1);
}

pair<int, pair<int, int>> MaxHeap::getMax() {
    return vect->at(0);
}

pair<int, pair<int, int>> MaxHeap::extractMax() {
    auto max = vect->at(0);    
    swap(0, vect->size() - 1);
    vect->pop_back();
    posiciones->erase(max.second);
    shiftDown(0);
    return max;
}

void MaxHeap::shiftDown(int index) {
    int size = vect->size();
    if (size > 1) {        
        int n = vect->at(index).first;
        int leftIndex = left(index);
        int rightIndex = right(index);
        if (leftIndex >= size)
            return;
        int l = vect->at(leftIndex).first;
        int r = -1;
        if (rightIndex < size)
            r = vect->at(rightIndex).first;
        
        if (n < l) // izquierda es mayor que parent
            if (l > r) {
                int li = left(index);
                swap(index, li);
                shiftDown(li);
                return;
            }
        if (n < r) {
            int ri = right(index);
            swap(index, ri);
            shiftDown(ri);
            return;
        }
    }
}

void MaxHeap::insert(std::pair<int, int> pair) {
    int index = getIndex(pair);
    if (index == -1) {
        auto entry = make_pair(1, pair);
        vect->push_back(entry);
        posiciones->insert(make_pair(pair, vect->size() - 1));
        shiftUp(vect->size() - 1);
    } else {
        updateFrequency(pair, 1);
    }
}

void MaxHeap::shiftUp(int index) {
    if (vect->size() > 1) {
        int n = vect->at(index).first;
        int p = vect->at(parent(index)).first;
        if (n > p) {
            int pi = parent(index);
            swap(index, pi);
            shiftUp(pi);
            return;
        }
    }
}

void MaxHeap::updateFrequency(std::pair<int, int> pair, int change) {
    /// buscar
    int index = getIndex(pair);
    if (index == -1)
        return;

    vect->at(index).first += change;
    if (vect->at(index).first <= 0) {
        delete_pair(pair);
    }
    else if (change < 0) {
        shiftDown(index);
    } else {
        shiftUp(index);
    }
}

void MaxHeap::delete_pair(std::pair<int, int> pair) {
    int index = getIndex(pair);
    if (index == -1)
        return;
    if (index == vect->size() - 1) {
        vect->pop_back();        
    } else {
        swap(index, vect->size() - 1);
        vect->pop_back();
        shiftDown(index);
    }
    posiciones->erase(pair);    
}

void MaxHeap::printHeap() {
    cout << "heap = [ ";
    auto it_vect = vect->begin();
    while(it_vect < vect->end()) {
        cout << "(" << it_vect->first << ", {" << it_vect->second.first << ", " << it_vect->second.second << "}), ";
        it_vect++;
    }
    cout << "]" << endl;
}

void MaxHeap::printIndexes() {
    cout << "indexes = [ ";
    auto it_map = posiciones->begin();
    while(it_map != posiciones->end()) {
        cout << "({" << it_map->first.first << ", " << it_map->first.second << "}, " << it_map->second << "), ";
        it_map++;
    }
    cout << "]" << endl;
}

std::vector<std::pair<int, std::pair<int, int>>>::iterator  MaxHeap::begin(){
    auto it = this->vect->begin();
    return it;
}

std::vector<std::pair<int, std::pair<int, int>>>::iterator  MaxHeap::end(){
    auto it = this->vect->end();
    return it;
}

int MaxHeap::parent(int index){
    return (index - 1) / 2;
}

int MaxHeap::left(int index){
    return (index*2) + 1;
}

int MaxHeap::right(int index){
    return (index*2) + 2;
} 