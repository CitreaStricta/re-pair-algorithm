#include "controller/controller.h"
#include <iostream>
// #include <iterator>

using namespace std;
int main()
{
    controller *c = new controller();

    c->addSequence(100);
    c->printListU();
    c->sUno();
    c->sDos();
    c->printListU();
    c->printListD();
    delete c;
    return 0;
}