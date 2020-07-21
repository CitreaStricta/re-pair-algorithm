#include "../LinkedList/LinkedList.h"
#include "../solDos/MaxHeap.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
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
    void sDos();
    void addSequence(int);
    void printListU();
    void printListD();
    void compress();
};