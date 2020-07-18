#include "controller/controller.h"
#include <iostream>
#include "Solucion2/Solucion2.h"
// #include <iterator>

using namespace std;
int main()
{
    controller *c = new controller();

    c->addSequence(200);
    Solucion2* sol2 = new Solucion2(c->listD);
    c->printListD();
    sol2->compress();

    sol2->printCompress();    
    // while (it+1 < vec->end()) {
    //     auto pair = make_pair(*it, *(std::next(it, 1)));
    //     heap->insert(pair);
    //     it++;
    // }
    //
    // heap->printHeap();
    // heap->printIndexes();
    //
    // cout << "aumentar frecuencia" << endl;
    //
    // heap->insert(make_pair(8, 6));
    // heap->insert(make_pair(8, 6));
    // heap->insert(make_pair(8, 6));
    //
    // heap->printHeap();
    // heap->printIndexes();
    //
    // cout << "get max" << endl;
    // auto max = heap->getMax();
    // cout << "(" << max.first << ", {" << max.second.first << ", " << max.second.second << "})" << endl;
    // heap->printHeap();
    // heap->printIndexes();
    //
    // cout << "extract max" << endl;
    // heap->extractMax();    
    // heap->printHeap();
    // heap->printIndexes();
    //
    // cout << "updateFrequency" << endl;
    // heap->updateFrequency(make_pair(4, 6), -1);    
    // heap->printHeap();
    // heap->printIndexes();
    //
    // controller *c = new controller();
    // c->addSequence(1000);
    // c->printList();
    // c->iterCompress();
    //
    // while(!c->reglaFinal->empty())
    // {
    //     cout << c->reglaFinal->front() << " ";
    //     c->reglaFinal->pop();
    // }
    // cout << endl;
    //
    // delete c;
    // return 0;
    //delete c;
    //delete sol2;
    return 0;
}