#include "../LinkedList/LinkedList.h"
#include "../solUno/solUno.h"
#include <iostream>
#include <utility>
#include <stack>
#include <queue>
#include <map>

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
    void sUno();
    void addSequence(int);
    void printList();
};