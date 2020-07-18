#include "controller.h"
#include <iostream>
#include <iterator>
#include "./Solucion2/MaxHeap.h"

using namespace std;


int main()
{
    vector<int>* vec = new vector<int>();
    int arr[21] = {0, 1, 5, 4, 1, 5, 6, 8, 3, 4, 6, 8, 9, 5, 4, 1, 5, 6, 8, 6, 9};
    for (int i = 0; i < 21; i++)
        vec->push_back(arr[i]);

    MaxHeap* heap = new MaxHeap();
    
    auto it = vec->begin();

    while (it+1 < vec->end()) {
        auto pair = make_pair(*it, *(std::next(it, 1)));
        heap->insert(pair);
        it++;
    }

    heap->printHeap();
    heap->printIndexes();

    cout << "aumentar frecuencia" << endl;

    heap->insert(make_pair(8, 6));
    heap->insert(make_pair(8, 6));
    heap->insert(make_pair(8, 6));

    heap->printHeap();
    heap->printIndexes();

    cout << "get max" << endl;
    auto max = heap->getMax();
    cout << "(" << max.first << ", {" << max.second.first << ", " << max.second.second << "})" << endl;
    heap->printHeap();
    heap->printIndexes();

    cout << "extract max" << endl;
    heap->extractMax();    
    heap->printHeap();
    heap->printIndexes();

    cout << "updateFrequency" << endl;
    heap->updateFrequency(make_pair(4, 6), -1);    
    heap->printHeap();
    heap->printIndexes();

    // controller *c = new controller();
    // c->addSequence(1000);
    // c->printList();
    // c->iterCompress();

    // while(!c->reglaFinal->empty())
    // {
    //     cout << c->reglaFinal->front() << " ";
    //     c->reglaFinal->pop();
    // }
    // cout << endl;
    
    // delete c;
    // return 0;
}