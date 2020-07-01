#include "controller.h"
#include <iostream>

using namespace std;

int main()
{
    controller *c = new controller();
    c->addSequence(50);
    c->printList();
    c->iterCompress();
    delete c;
    return 0;
}