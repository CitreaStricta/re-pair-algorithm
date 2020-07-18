#ifndef MH_H
#define MH_H

#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

class MaxHeap
{
private:
    int parent(int index);
    int left(int index);
    int right(int index);
    int getIndex(std::pair<int, int> pair);
    void updateIndex(std::pair<int, int> pair, int newIndex);
    std::map<pair<int, int>, int>* posiciones;
    vector<pair<int, pair<int, int>>>* vect;
public:
    MaxHeap();
    ~MaxHeap();
    std::pair<int, std::pair<int, int>> getMax(); 
    std::pair<int, std::pair<int, int>> extractMax();
    void swap(int i1, int i2);
    void insert(std::pair<int, int> pair);
    void shiftUp(int index);
    void updateFrequency(std::pair<int, int> pair, int change); 
    void shiftDown(int index);
    void delete_pair(std::pair<int, int> pair); 
    void printHeap();
    void printIndexes();
    std::vector<std::pair<int, std::pair<int, int>>>::iterator begin();
    std::vector<std::pair<int, std::pair<int, int>>>::iterator end();
};

#endif