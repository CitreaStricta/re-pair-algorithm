#include "../LinkedList/LinkedList.h"
#include "MaxHeap.h"
#include "str.h"
#include <iostream>
#include <map>

using namespace std;

class solDos
{
private:
    MaxHeap *maxHeap;
    map<pair<int, int>, str> *_map;
    LinkedList *list;
public:
    solDos();
    ~solDos();
    void Compress(LinkedList *l);
    MaxHeap* fillHeap();
};