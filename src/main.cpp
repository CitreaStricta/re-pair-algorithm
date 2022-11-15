#include "controller/controller.h"
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
    controller *c = new controller();

    double time = (double) 0;
    double time2 = (double) 0;
    // a mas "rep" mayor el tiempo de ejecucion pero mayor la precision del tiempo que toma la ejecucion
    int rep = 1; 
    clock_t start;

    int n = (int) stoi(argv[1]);
    cout << n << endl << endl;
    for (int i = 0; i < rep; i++)
    {
        c->addSequence(n);

        // start = clock();
        // c->sUno();
        // time += (double) ((double)clock() - (double)start) / CLOCKS_PER_SEC;
        // cout << "Tamanio de la LL1 despues de compresion: " << c->listU->size() << endl;

        start = clock();
        c->sDos();
        time2 += (double) ((double)clock() - (double)start) / CLOCKS_PER_SEC;
        cout << "Tamanio de la LL2 despues de compresion: " << c->listD->size() << endl;
        cout << endl;
    }

    //cout << "Tiempo promedio sol.1: " << fixed << setprecision(10) << time/((double)(rep)) << endl;
    cout << "Tiempo promedio sol.2: " << fixed << setprecision(10) << time2/((double)(rep)) << endl;

    delete c;
    return 0;
}