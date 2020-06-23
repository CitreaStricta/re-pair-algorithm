#include <iostream>
#include "controller.h"

using namespace std;

int main()
{
    controller *c = new controller();
    c->addSequence(50);
    c->printList();
    delete c;
    return 0;
}