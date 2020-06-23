#include "controller.h"
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

controller::controller()
{
    srand(time(NULL));
    list = new LinkedList();
}

controller::~controller()
{
    delete list;
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
    delete list;
    list = new LinkedList();
    for (int i = 0; i < n; i++)
    {
        list->insertAtTail(1 + rand() % 27);
    }
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