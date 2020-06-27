#include "LinkedList/LinkedList.h"

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
    map<pair<int,int>, int>* fillMap();
};