#include "LinkedList/nodo.h"
#include "controller.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>
#include <time.h>
#include <map>

using namespace std;

controller::controller()
{
    srand(time(NULL));
    reglas = new stack<pair<int, pair<int, int>>>();
    reglaFinal = new queue<int>();
    list = nullptr;
}

controller::~controller()
{
    if(list != nullptr) delete list;
    delete reglas;
    delete reglaFinal;
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
    
    // si se quiere llenar la lista con una secuencia custom
    // int a;
    // for (int i = 0; i < 50; i++)
    // {
    //     cin >> a;
    //     list->insertAtTail(a);
    // }
    
    for (int i = 0; i < n; i++)
    {
        list->insertAtTail(1 + rand() % 27);
    }
}

// hace lo que crees que hace
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


// METODOS DE LA 1ERA SOLUCION

void controller::iterParCompress(int regla, pair<int, int> par)
{
    Iterator it = list->begin();
    nodo *nodoH = list->head;

    while(it.nodo()->next != it.end())
    {
        if(it.nodo()->n == par.first &&
           it.nodo()->next->n == par.second)
        {
            it.nodo()->n = regla;
            list->popAt(it.nodo()->next);
            // esto es para el extranio caso de que el par este al final de la lista
            // si ese fuera el caso, el while se queda en un loop infinito por temas
            // de la implementacion
            if(it.nodo()->next == it.end()) break;
        }
        it++;
    }
}

void controller::iterCompress()
{
    int regla = 28;
    if(list->size() == 0)
    {
        cout << "no hay elementos para comprimir."
        "Ejecuta addSequence antes que iterCompress" << endl;
        return;
    }

    map<pair<int,int>, int> *m;
    while(true)
    {
        m = fillMap();

        // ESTO NOS DICE CUAL ES EL PAR QUE MAS SE REPITE EN LA LISTA
        // (ESO SI, NO NECESARIAMENTE EL 1ER PAR REPETIDO)
        map<pair<int,int>, int>::iterator BEEG;

        BEEG = max_element(m->begin(),m->end(),[]
        (const pair<pair<int,int>, int>& a, const pair<pair<int,int>, int>& b)->bool
        {return a.second < b.second;});
        pair<int, int> replace = BEEG->first;

        cout << "Max is: " << BEEG->first.first << " " << BEEG->first.second << ", " << BEEG->second << endl;
        cout << "Tenemos que reemplasar el par: " << replace.first << " " << replace.second<< endl;

        // cuando ningun par se repita mas de dos veces,
        // se creara la ultima regla la esta en un string
        if(BEEG->second == 1)
        {
            nodo *nodoH = list->head;
            
            Iterator it = list->begin();
            reglaFinal->push(regla);
            while(nodoH->next != list->tail)
            {
                reglaFinal->push(nodoH->next->n);
                list->popAt(nodoH->next);
            }
            // quita el ultimo espacio
            delete m;
            break;
        }

        // Buscar y, al mismo tiempo, cambiar el par encontrado por la regla 28, 29, ..., n
        iterParCompress(regla, replace);
        reglas->push(make_pair(regla++, replace));
        delete m;
    }
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
    Iterator it = list->begin();
    // creo un pair auxiliar para manejar los valores
    pair<int, int> pAux;
    // cuando la tail de la LL se alcance entonces no quedaran mas
    // valores en la LL por los cuales iterar
    map<pair<int,int>, int>::iterator itMap;
    while(it.nodo()->next != it.end())
    {
        pAux = make_pair(it.nodo()->n, it.nodo()->next->n);
        itMap = m->find(pAux);

        if(itMap != m->end())
            itMap->second++;
        else
            m->insert(make_pair(pAux, 1));

        it++;
    }
    auto itMap2 = m->begin();

    while(itMap2 != m->end())
    {
        cout << itMap2->first.first << " " << itMap2->first.second << ", " << itMap2->second << endl;
        itMap2++;
    }

    return m;
}