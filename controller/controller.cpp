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
    // if(listU == nullptr)
    // {
    //     cout << "1ero ejecuta addSequence" << endl;
    //     return;
    // }

    // solUno *sUno = new solUno();
    // respUno = sUno->Compress(listU);
    // delete sUno;
}

void controller::sDos()
{
    if(listU == nullptr)
    {
        cout << "1ero ejecuta addSequence" << endl;
        return;
    }

    solDos *sDos = new solDos();
    sDos->Compress(listD);
    delete sDos;
}

// hace lo que crees que hace
void controller::printListU()
{
    respUno;
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
    respUno;
    int aux = listU->at(0);
    int i = 1;
    while(aux > 0)
    {
        cout << aux << " ";
        aux = listU->at(i++);
    }
    cout << endl;
}