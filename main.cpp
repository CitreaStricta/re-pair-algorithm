#include "controller.h"
#include <iostream>
#include <iterator>

using namespace std;


int main()
{
    controller *c = new controller();
    c->addSequence(50);
    c->printList();
    c->iterCompress();

    while(!c->reglaFinal->empty())
    {
        cout << c->reglaFinal->front() << " ";
        c->reglaFinal->pop();
    }
    cout << endl;
    
    delete c;
    return 0;
}