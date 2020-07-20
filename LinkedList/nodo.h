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

static void fixOccPtr(nodo* nodo) {
	if (nodo->nextOcurr != nullptr) {
        if (nodo->prevOcurr != nullptr) {
            nodo->nextOcurr->prevOcurr = nodo->prevOcurr;
            nodo->prevOcurr->nextOcurr = nodo->nextOcurr;
        } else {
            nodo->nextOcurr->prevOcurr = nullptr;
        }
    } else {
        if (nodo->prevOcurr != nullptr) {
            nodo->prevOcurr->nextOcurr = nullptr;
        }
    }
}

#endif