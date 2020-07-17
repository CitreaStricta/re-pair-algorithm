#include "LinkedList2.h"

// La lista se basa en la suposicion de que el puntero del ultimo nodo siempre es nullptr
LinkedList2::LinkedList2()
{
    // ambos nodos, head y tail, estan apuntando, con next y prev
    // respectivamente, a tail y head respectivamente
    head = new nodo2();
    head->next = tail;
    head->n = -2;
    head->prev = nullptr;
    
    tail = new nodo2();
    tail->prev = head;
    tail->n = -2;
    tail->next = nullptr;
    mysize = 0;
}

LinkedList2::~LinkedList2()
{
    /**
     * Algo interesante que esta ocurriendo es que, por alguna razon,
     * el puntero delete_Aux que se esta creando aqui, esta apuntando
     * a la misma direccion de memoria que "this" al momento de su
     * creacion, es decir, apunta a esta instancia de LinkedList2.
     * No se porque si. Igual lo voy a desrreferenciar al momento
     * de su creacion por si acaso.
    **/
    nodo2 *delete_Aux = nullptr;

    //mientras que head siga apuntando a algo
    while(head->next != nullptr)
    {
        // desrreferencia el prev del nodo siguiente de head por seguridad
        head->next->prev = nullptr;
        // apunta delete_Aux al nodo que sigue de head
        delete_Aux = head->next;
        // apunto el next de head al nodo subsiguiente de head
        head->next = head->next->next;
        // desreferencia el next y prev del nodo a eliminar por seguridad
        delete_Aux->prev = delete_Aux->next = nullptr;
        delete delete_Aux;
    }

    delete head;
    mysize = 0;
}

void LinkedList2::insertAtTail(int n)
{
    // creo el nuevo nodo
    nodo2 *aux = new nodo2();
    // le entrego su valor
    aux->n = n;
    // apunto next de aux a tail
    aux->next = tail;
    // apunto prev de aux al prev de tail
    aux->prev = tail->prev;
    // ahora hago una wea mas "wtf" que la chucha
    // apunto el next (de lo que ahora esta apuntando el prev de aux)
    // a aux
    aux->prev->next = aux;
    //y ahora algo parecido
    //apunto el prev (de lo que ahora esta apuntando el next de aux)
    // a aux
    aux->next->prev = aux;
    mysize++;
}

/*
 * resive el valor a guardar y un puntero
 * al nodo siguiente en donde voy a posicionar mi nuevo nodo
 *  
 * Ej: Si tengo [nodo0->nodo1->nodo2->nodo3->nodo4]
 * y quiero colocar un nodo en la pocision 4, entonces
 * el metodo tiene que resivir un puntero al [nodo3]
 * ([nodo2->next] en este caso)
*/
void LinkedList2::insertAt(int n, nodo2* k)
{
    // creo el nuevo nodo
    nodo2 *aux = new nodo2();
    // le entrego su valor
    aux->n = n;
    // apunto el next de aux a k
    aux->next = k;
    // apunto el prev de aux a lo que el prev de k esta apuntando
    aux->prev = k->prev;

    // ahora hago una wea mas "wtf" que la chucha //

    // apunto el next
    // (del nodo que esta siendo apuntando por el prev de aux)
    // a aux
    aux->prev->next = aux;
    // apunto el prev
    // (del nodo que esta siendo apuntando por el next de aux)
    // a aux
    aux->next->prev = aux;
    mysize++;
}

/*
 * resive un puntero al nodo a eliminar
 * 
 * Ej: Si tengo [nodo0->nodo1->nodo2->nodo3->nodo4]
 * y quiero eliminar el nodo en la pocision 2, entonces
 * el metodo tiene que resivir un puntero al [nodo1]
 * ([nodo0->next] en este caso)
*/
void LinkedList2::popAt(nodo2 *k)
{   
    // creo mi nodo auxiliar y lo apunto al nodo a popear
    nodo2 *pop_Aux = k;
    // apunto el next
    // (del nodo que esta siendo apuntando por el prev de pop_Aux)
    // al nodo que esta diendo apuntado por el next de pop_Aux
    pop_Aux->prev->next = pop_Aux->next;
    // apunto el prev
    // (del nodo que esta siendo apuntando por el next de pop_Aux)
    // al nodo que esta diendo apuntado por el prev de pop_Aux
    pop_Aux->next->prev = pop_Aux->prev;
    // desreferencio a los punteros prev y next de pop_aux por seguridad
    pop_Aux->prev = pop_Aux->next = nullptr;
    // y ahora puedo popear con seguridad el nodo pop_Aux
    // (actually delete it like a boss. WARAAAAAP)
    delete pop_Aux;
    mysize--;
}

// retorna un puntero nodo apuntando al 1er nodo, es decir,
// el nodo que viene despues de "head"
nodo2* LinkedList2::getPtrAt0()
{
    return head->next;
}

// Accede al i-esimo elemento de la lista
int LinkedList2::at(int pos)
{
    if(pos < 0 || pos > mysize - 1)
    {
        return -1;
    }

    // Itero el puntero "aux_at" hasta que "aux" sea igual a la posicion buscada
    nodo2 *aux_at = head->next;
    while(pos--)
        aux_at = aux_at->next;
    return aux_at->n;
}

int LinkedList2::size()
{
    return mysize;
}

Iterator2 LinkedList2::begin(){
    Iterator2 it = Iterator2(getPtrAt0(), tail);
    return it;
}