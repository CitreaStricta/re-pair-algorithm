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
        << endl;
        return;
    }

    // mientras que la frecuencia del par mas repetido sea distinto de 1, continua
    auto replace = return_most_freq();
    while(replace.second != 1)
    {
        ParCompress(rule, replace.first); // O(n)

        // Buscar y cambiar el par encontrado por la rule 28, 29, ..., [rule]
        replace = return_most_freq(); // O(n*logn)

        // cout << replace.first.first << " " << replace.first.second << ", " << replace.second << endl;

        rule++;
    }
    return;
}

pair<pair<int,int>, int> solUno::return_most_freq()
{
    map<pair<int,int>, int> *m = new map<pair<int,int>, int>();
    auto big = make_pair(make_pair(1, 1), 1);

    //////////iteracion en la linked list//////////
    // creo un puntero nodo que apunta al 1er nodo de la lista

    // cuando la tail de la LL se alcance entonces no quedaran mas
    // valores en la LL por los cuales iterar
    map<pair<int,int>, int>::iterator itMap;
    Iterator it = list->begin();
    pair<int, int> pAux;
    
    while(it.hasNext()) // O(n)
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

    // mientras que haya un siguiente nodo, continua
    while(it.hasNext())
    {
        if(it.nodo()->n == par.first &&
           it.nodo()->next->n == par.second)
        {
            it.nodo()->n = regla;
            list->popAt(it.nodo()->next);

            // por temas con la LL, es necesario revisar
            // si el siguiente elemento en ella es la "tail"
            // si no se revisa, el programa quedara atrapado el el while
            if(!it.hasNext()) break;
        }
        it++;
    }
}