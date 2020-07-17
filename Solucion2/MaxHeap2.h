#include <utility>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class MaxHeap2
{
private:
    int _size = 0;    
    int parent(int index) { return (index - 1) / 2; }; 
    int left(int index) { return (index*2) + 1; }; 
    int right(int index) { return (index*2) + 2; }; 
    int getIndex(std::pair<int, int> pair);
    void updateIndex(std::pair<int, int> pair, int newIndex);
    vector<pair<int, pair<int, int>>>* vect;
    std::map<pair<int, int>, int>* posiciones;
public:
    MaxHeap2();
    ~MaxHeap2();
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
};