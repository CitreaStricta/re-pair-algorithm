#include "controller.h"

using namespace std;

controller::controller()
{
    srand(time(NULL));
    respUno = respDos = nullptr;
    listU = listD = nullptr;
}

controller::~controller()
{
    if(listU != nullptr) delete listU;
    if(listD != nullptr) delete listD;
    delete respUno;
    delete respDos;
}

/**
 * Recibe el tamanio de la secuencia a comprimir
 * (la secuencia sera creada a partir de numeros
 * aleatorios entre el 1 y el 27)
 * 
 * Si "addSequence" se vuelve a ejecutar, la secuencia
 * anterior sera borrada.
**/
void controller::addSequence(int n)
{
    if(listU != nullptr) delete listU;
    if(listD != nullptr) delete listD;
    listU = new LinkedList();
    listD = new LinkedList();
    // int abc[28] = {1, 2, 3, 2, 3, 1, 1, 1, 2, 4, 2, 4, 2, 4, 24, 4, 12, 4, 24, 4, 1, 1, 20, 21, 23, 23, 23, 12};
    // int abc[9] = {1, 3, 5, 1, 3, 7, 5, 1, 3};
    int aux;
    for (int i = 0; i < n; i++)
    {
        aux = 1 + rand() % 27;
        listU->insertAtTail(aux);
        listD->insertAtTail(aux);

    }
}

void controller::sDos()
{
    if(listU == nullptr)
    {
        cout << "1ero ejecuta addSequence" << endl;
        return;
    }

    MaxHeap *h = new MaxHeap();
    h->Compress(listD);
    delete h;
}

// hace lo que crees que hace
void controller::printListU()
{
    int aux = listU->at(0);
    int i = 1;
    while(aux > 0)
    {
        cout << aux << " ";
        aux = listU->at(i++);
    }
    cout << endl;
}

void controller::printListD()
{
    int aux = listD->at(0);
    int i = 1;
    while(aux > 0)
    {
        cout << aux << " ";
        aux = listD->at(i++);
    }
    cout << endl;
}