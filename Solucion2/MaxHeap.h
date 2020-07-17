#include <utility>
#include <vector>
#include "HeapNode.h"
#include <map>

using namespace std;

class MaxHeap
{
private:
    int _size = 0;
    HeapNode* first = nullptr;
    HeapNode* last = nullptr;
    map<std::pair<int,int>, HeapNode*>* _map;
public:
    MaxHeap();
    ~MaxHeap();
    void insertItem(std::pair<int, int> pair, int* address);
    void deleteItem(std::pair<int, int> pair);    
};