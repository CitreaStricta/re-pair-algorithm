#ifndef MH_H
#define MH_H

#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include "str.h"
#define itM std::map<std::pair<int, int>, str>::iterator

using namespace std;

class MaxHeap
{
private:
    int parent(int index);
    int left(int index);
    int right(int index);
    itM getIndex(std::pair<int, int> pair);
    void updatePtrs(nodo*, map<pair<int, int>, str>::iterator);
    void _updatePtrs(nodo* nPtr, itM index);
    void updateIndex(std::pair<int, int> pair, int newIndex);
    nodo* compressing_ocurr(nodo* nPtr, int);
    std::map<pair<int, int>, str>* posiciones;
    vector<pair<int, pair<int, int>>>* vect;
    LinkedList *list;
public:
    MaxHeap();
    ~MaxHeap();
    void Compress(LinkedList *l);
    void compress_mustFreq(itM maxInMap, int);
    void fillHeapAndMap();
    std::pair<int, std::pair<int, int>> getMax();
    std::pair<int, std::pair<int, int>> extractMax();
    void swap(int i1, int i2);
    void insert(std::pair<int, int> pair, nodo*);
    void shiftUp(int index);
    void updateFrequency(map<pair<int, int>, str>::iterator iterMap, int change); 
    void shiftDown(int index);
    void delete_pair(map<pair<int, int>, str>::iterator iterMap); 
    void printHeap();
    void printIndexes();
    std::vector<std::pair<int, std::pair<int, int>>>::iterator begin();
    std::vector<std::pair<int, std::pair<int, int>>>::iterator end();
};

#endif