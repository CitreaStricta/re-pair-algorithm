#include "nodo2.h"
class Iterator2
{
private:
    struct nodo2* _begin;
    struct nodo2* _end;
    struct nodo2* _nodo;    
public:
    Iterator2(struct nodo2* begin, struct nodo2* end);
    ~Iterator2();
    Iterator2& operator++(int);
    Iterator2& operator--(int);
    void goToStart();
    struct nodo2* begin();
    struct nodo2* end();
    struct nodo2* nodo(); 
};