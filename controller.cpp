#include "controller.h"
#include <iostream>
#include <random>
#include <time.h>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

controller::controller()
{
    srand(time(NULL));
    list = nullptr;
}

controller::~controller()
{
    if(list != nullptr) delete list;
}

/**
 * Resive el tamanio de la secuencia a comprimir
 * (la secuencia sera creada a partir de numeros
 * aleatorios entre el 1 y el 27)
 * 
 * Si "addSequence" se vuelve a ejecutar, la secuencia
 * anterior sera borrada.
**/
void controller::addSequence(int n)
{
    if(list != nullptr) delete list;
    list = new LinkedList();
    for (int i = 0; i < n; i++)
    {
        list->insertAtTail(1 + rand() % 27);
    }
}

void controller::iterCompress()
{
    if(list->size() == 0)
    {
        cout << "no hay elementos para comprimir."
        "Ejecuta addSequence antes que iterCompress" << endl;
        return;
    }

    map<pair<int,int>, int> *m = fillMap();

    // ESTO NOS DICE CUAL ES EL PAR QUE MAS SE REPITE EN LA LISTA
    // (ESO SI, NO NECESARIAMENTE EL 1ER PAR REPETIDO)
    map<pair<int,int>, int>::iterator best;

    best = max_element(m->begin(),m->end(),[]
    (const pair<pair<int,int>, int>& a, const pair<pair<int,int>, int>& b)->bool
    {return a.second < b.second;});
    auto replace = best->first;
    cout << "Max is: " << best->first.first << " " << best->first.second << ", " << best->second << endl;
    cout << "Tenemos que reemplasar el par: " << replace.first << " " << replace.second<< endl;

    delete m;
}

map<pair<int,int>, int>* controller::fillMap()
{
    map<pair<int,int>, int> *m = new map<pair<int,int>, int>();
    if(list->size() == 0)
    {
        cout << "no hay elementos para comprimir."
        "Ejecuta addSequence antes que iterCompress" << endl;
        delete m;
        return m;
    }

    //////////iteracion en la linked list//////////
    // creo un puntero nodo que apunta al 1er nodo de la lista
    nodo *pNodo = list->getPtrAt0();
    // creo un pair auxiliar para manejar los valores
    pair<int, int> pAux;
    // cuando la tail de la LL se alcance entonces no quedaran mas
    // valores en la LL por los cuales iterar
    while(pNodo->next != list->tail)
    {
        pAux = make_pair(pNodo->n, pNodo->next->n);
        auto it2 = m->find(pAux);

        if(it2 != m->end())
            it2->second++;
        else
            m->insert(make_pair(pAux, 1));

        pNodo = pNodo->next;
    }
    auto it2 = m->begin();

    while(it2 != m->end())
    {
        cout << it2->first.first << " " << it2->first.second << ", " << it2->second << endl;
        it2++;
    }
    return m;
}

// printea lo que esta en la lista (sin sacarlo)
void controller::printList()
{
    int aux = list->at(0);
    int i = 1;
    while(aux > 0)
    {
        cout << aux << " ";
        aux = list->at(i++);
    }
    cout << endl;
}