#include "LinkedList/LinkedList.h"

class controller
{
private:
    LinkedList *list;
public:
    controller();
    ~controller();
    void addSequence(int n);
    void printList();
};