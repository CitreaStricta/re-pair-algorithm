#include "MaxHeap2.h"

MaxHeap2::MaxHeap2(){
    vect = new vector<pair<int, pair<int, int>>>();
}

MaxHeap2::~MaxHeap2(){
    delete vect;
}

void MaxHeap2::swap(int i1, int i2) {
    auto aux = vect->at(i1);
    vect->at(i1) = vect->at(i2);
    vect->at(i2) = aux;
}

pair<int, pair<int, int>> MaxHeap2::getMax() {
    return vect->at(0);
}

pair<int, pair<int, int>> MaxHeap2::extractMax() {
    auto max = vect->at(0);
    swap(0, vect->size() - 1);    
    vect->pop_back();
    shiftDown(0);
}

void MaxHeap2::shiftDown(int index){
    int n = vect->at(index).first;
    int l = vect->at(left(index)).first;
    int r = vect->at(right(index)).first;    
    if (n < l)  // izquierda es mayor que parent
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

void MaxHeap2::insert(std::pair<int, int> pair){
    if (false) {
        auto entry = make_pair(1, pair);
        vect->push_back(entry);
        shiftUp(vect->size() - 1);        
    } else {
        increaseFrequency(pair);
    }
}

void MaxHeap2::shiftUp(int index){
    int n = vect->at(index).first;
    int p = vect->at(parent(index)).first;
    if (n > p) { 
        int pi = parent(index);
        swap(index, pi);
        shiftUp(pi);
        return;
    }        
}

void MaxHeap2::increaseFrequency(std::pair<int, int> pair){
    /// buscar
    int index = 0;

    /// aumentar frecuencia

    /// shift up
    shiftUp(index);    
}


void MaxHeap2::delete_pair(std::pair<int, int> pair){
    
}
