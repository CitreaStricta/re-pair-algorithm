#include "../LinkedList/LinkedList.h"
#include "../Solucion2/MaxHeap.h"
#include "../SolUno/solUno.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct helper {
    nodo *first;
    nodo *last;
    int heapIndex;
};

class controller
{
private:
    vector<pair<int, pair<int, int>>> *respUno;
    vector<pair<int, pair<int, int>>> *respDos;
public:
    LinkedList *listU;
    LinkedList *listD;
    controller();
    ~controller();
    void sUno();
    void sDos();
    void addSequence(int);
    void printListU();
    void printListD();
    void compress();
};