#ifndef STR_H
#define STR_H

#include "../LinkedList/nodo.h"

struct str
{
    // ptr a la 1era ocurrencia del par
    nodo *first;
    // ptr a la ultima ocurrencia del par
    nodo *last;
    // indice del par en el Heap
    int heapIndex;
};

#endif