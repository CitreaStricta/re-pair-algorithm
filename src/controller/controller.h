#include "../LinkedList/LinkedList.h"
#include "../solDos/MaxHeap.h"
#include "../solUno/solUno.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
class controller
{
private:
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