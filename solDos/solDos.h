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
public:
    solDos();
    ~solDos();
    void Compress(LinkedList *l);
};