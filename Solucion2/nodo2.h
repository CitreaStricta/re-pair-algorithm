#ifndef NODO_H
#define NODO_H

struct nodo2
{
	int n;
	nodo2 *next;
	nodo2 *prev;
    nodo2 *prev_ocur;
    nodo2 *next_ocur;
};

#endif