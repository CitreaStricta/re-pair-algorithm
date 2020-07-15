#include "LinkedList/LinkedList.h"
#include <iostream>
#include <utility>
#include <stack>
#include <queue>
#include <map>

using namespace std;

class controller
{
private:
public:
    stack<pair<int, pair<int, int>>> *reglas;
    queue<int> *reglaFinal;
    LinkedList *list;
    controller();
    ~controller();
    void addSequence(int);
    void iterCompress();
    void iterParCompress(int, pair<int, int>);
    void printList();
    map<pair<int, int>, int>* fillMap();
};