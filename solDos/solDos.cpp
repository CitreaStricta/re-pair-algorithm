#include "solDos.h"

solDos::solDos()
{
    _map = new map<pair<int, int>, str>();
}

solDos::~solDos()
{
    delete maxHeap;
    delete _map;
}

void solDos::Compress(LinkedList *l)
{
    list = l;
    MaxHeap *h = fillHeap();
    h->Compress(list);
}

MaxHeap* solDos::fillHeap()
{
    MaxHeap *h = new MaxHeap();
    if(list->size() == 0)
    {
        cout << "no hay elementos para comprimir."
        "Ejecuta addSequence antes que iterCompress" << endl;
        delete h;
        return h;
    }

    //////////iteracion en la linked list//////////
    // creo un puntero nodo que apunta al 1er nodo de la lista
    Iterator it = list->begin();
    // creo un pair auxiliar para manejar los valores
    pair<int, int> pAux;
    // cuando la tail de la LL se alcance entonces no quedaran mas
    // valores en la LL por los cuales iterar
    while(it.nodo()->next != it.end())
    {
        pAux = make_pair(it.nodo()->n, it.nodo()->next->n);
        h->insert(pAux, it.nodo());
        it++;
    }


    // //////////iteracion en la linked list//////////
    // // creo un puntero nodo que apunta al 1er nodo de la lista
    // Iterator it = list->begin();
    // // creo un pair auxiliar para manejar los valores
    // pair<int, int> pAux;
    // // cuando la tail de la LL se alcance entonces no quedaran mas
    // // valores en la LL por los cuales iterar
    // map<pair<int,int>, str>::iterator itMap = _map->begin();
    // while(it.nodo()->next != it.end())
    // {
    //     pAux = make_pair(it.nodo()->n, it.nodo()->next->n);
    //     itMap = h->find(pAux);
    //
    //     if(itMap != m->end())
    //         itMap->second++;
    //     else
    //         m->insert(make_pair(pAux, 1));
    //
    //     it++;
    // }
    // auto itMap2 = m->begin();
    //
    // while(itMap2 != m->end())
    // {
    //     cout << itMap2->first.first << " " << itMap2->first.second << ", " << itMap2->second << endl;
    //     itMap2++;
    // }
    //
    // return m;
}