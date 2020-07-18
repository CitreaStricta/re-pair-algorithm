#include "controller.h"
#include <iostream>
#include <iterator>

using namespace std;


int main()
{
    controller *c = new controller();

    c->addSequence(50);
    c->printList();
    c->sUno();
    c->printList();

    delete c;
    return 0;
}