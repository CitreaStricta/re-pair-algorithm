#include "controller.h"

using namespace std;

controller::controller()
{
    srand(time(NULL));
    listU = listD = nullptr;
}

controller::~controller()
{
    if(listU != nullptr) delete listU;
    if(listD != nullptr) delete listD;
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
    int aux;
    for (int i = 0; i < n; i++)
    {
        aux = 1 + rand() % 27;
        listU->insertAtTail(aux);
        listD->insertAtTail(aux);
    }
}

void controller::sUno()
{
    if(listU == nullptr)
    {
        cout << "1ero ejecuta addSequence" << endl;
        return;
    }

    solUno *su = new solUno();
    su->Compress(listU);
    delete su;
}

void controller::sDos()
{
    if(listD == nullptr)
    {
        cout << "1ero ejecuta addSequence" << endl;
        return;
    }

    MaxHeap *sd = new MaxHeap();
    sd->Compress(listD);
    delete sd;
}

// hace lo que crees que hace
void controller::printListU()
{
    cout << "Tamanio lista sol1: " << listU->size() << endl;;
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
    cout << "Tamanio lista sol2: " << listD->size() << endl;
    int aux = listD->at(0);
    int i = 1;
    while(aux > 0)
    {
        cout << aux << " ";
        aux = listD->at(i++);
    }
    cout << endl;
}