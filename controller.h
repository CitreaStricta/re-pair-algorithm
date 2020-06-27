#include "LinkedList/LinkedList.h"
#include <iostream>
#include <utility>
#include <map>

using namespace std;

class controller
{
private:
public:
    LinkedList *list;
    controller();
    ~controller();
    void addSequence(int n);
    void iterCompress();
    void printList();
    map<pair<int, int>, int>* fillMap();
};