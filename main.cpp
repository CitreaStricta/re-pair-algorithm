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
    int rep = 5;
    clock_t start;

    int n = (int) stoi(argv[1]);
    cout << n << endl << endl;
    cout << "Sol.1:" << endl;
    for (int i = 0; i < rep; i++)
    {
        c->addSequence(n);

        start = clock();
        c->sUno();
        time += (double) ((double)clock() - (double)start) / CLOCKS_PER_SEC;
        cout << c->listU->size() << endl;

        start = clock();
        c->sDos();
        time2 += (double) ((double)clock() - (double)start) / CLOCKS_PER_SEC;
        cout << c->listD->size() << endl;
    }

    cout << "Tiempo promedio sol.1: " << fixed << setprecision(10) << time/((double)(rep)) << endl;
    cout << "Tiempo promedio sol.2: " << fixed << setprecision(10) << time2/((double)(rep)) << endl;

    delete c;
    return 0;
}