#include "MaxHeap.h"
#include "../LinkedList/LinkedList.h"

struct reference {
    nodo *first;
    nodo *last;
    int* heapIndex;
};

class Solucion2
{
private:
    int replacement = 28;
    std::map<std::pair<int, int>, reference>* references;
    MaxHeap* maxHeap;
    LinkedList* list;
    void loadData();
    void compressPair(nodo* curNode, int index, int replacement);
    void deleteFromMap(std::pair<int, int> pair, nodo* nodo);
    void updateReference(std::pair<int, int> pair, nodo* nodo);
    void compressPairMejora3(nodo* curNode, int index, int replacement);
public:
    Solucion2(LinkedList* linkedList);
    ~Solucion2();
    void compress();
    void printCompress();
};