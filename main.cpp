#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
    auto ll = new LinkedList();

    ll->insertAtTail(1);

    auto it = ll->begin();

    while(it.nodo() != it.end()) {
        cout << it.nodo()->n << endl;
        it++;
    }

    it.goToStart();
    ll->insertAtTail(2);
    ll->insertAtTail(3);

    while(it.nodo() != it.end()) {
        cout << it.nodo()->n << endl;
        it++;
    }

    delete ll;
}