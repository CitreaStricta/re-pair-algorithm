#include "solUno.h"

solUno::solUno(){}

solUno::~solUno(){}

// resive un puntero de tipo LinkedList,
// comprime los nodos de esta
void solUno::Compress(LinkedList *l)
{
    list = l;
    int rule = 28;
    if(list->size() < 2)
    {
        cout
        << "no hay suficientes elementos para intentar comprimir, o "
        << "ejecutaste sUno primero que addSequence."
        <<endl;
        return;
    }

    auto replace = return_most_repeated();
    while(replace.second != 0) // Complejidad [numero de pares] * [busqueda en el map] * [iteracion en la LL] ~ O(n*logn)
    {
        ParCompress(rule, replace.first);

        // Buscar y cambiar el par encontrado por la rule 28, 29, ..., [rule]
        replace = return_most_repeated();

        // cout << replace.first.first << " " << replace.first.second << ", " << replace.second << endl;
        rule++;
    }
    return;
}

pair<pair<int,int>, int> solUno::return_most_repeated()
{
    map<pair<int,int>, int> *m = new map<pair<int,int>, int>();
    auto big = make_pair(make_pair(1, 1), 0);



    //////////iteracion en la linked list//////////
    // creo un puntero nodo que apunta al 1er nodo de la lista
    Iterator it = list->begin();
    // creo un pair auxiliar para manejar los valores
    pair<int, int> pAux;
    // cuando la tail de la LL se alcance entonces no quedaran mas
    // valores en la LL por los cuales iterar
    map<pair<int,int>, int>::iterator itMap;
    
    while(it.nodo()->next != it.end())
    {
        pAux = make_pair(it.nodo()->n, it.nodo()->next->n);
        itMap = m->find(pAux); // O(n*Logn)

        if(itMap != m->end())
        {
            itMap->second++;
            if(itMap->second > big.second)
                big = make_pair(pAux, itMap->second);
        }
        else
            m->insert(make_pair(pAux, 1));
        it++;
    }

    delete m;
    return big;
}

void solUno::ParCompress(int regla, pair<int, int> par)
{
    Iterator it = list->begin();
    nodo *nodoH = list->head;

    while(it.nodo()->next != it.end())
    {
        if(it.nodo()->n == par.first &&
           it.nodo()->next->n == par.second)
        {
            it.nodo()->n = regla;
            list->popAt(it.nodo()->next);
            // esto es para el extranio caso de que el par este al final de la lista.
            // Si ese fuera el caso, el while se queda en un loop infinito
            if(it.nodo()->next == it.end()) break;
        }
        it++;
    }
}