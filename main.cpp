#include "controller/controller.h"
#include <iostream>
// #include <iterator>

using namespace std;
int main()
{
    controller *c = new controller();

    c->addSequence(10000);
    // c->printListU();
    cout << c->listU->size() << endl;
    // c->sUno();
    c->sDos();
    cout << c->listU->size() << endl;
    cout << c->listD->size() << endl;

    // c->printListU();
    // c->printListD();
    delete c;
    return 0;
}