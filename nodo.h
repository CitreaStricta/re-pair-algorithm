#ifndef NODO_H
#define NODO_H

struct nodo
{
	int n;
	nodo *next;
	nodo *prev;
	nodo *nextOcurr;
	nodo *prevOcurr;
};

#endif