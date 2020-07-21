#include "solUno.h"

solUno::solUno(){}

solUno::~solUno(){}

// resive un puntero de tipo LinkedList,
// comprime los nodos de esta y devuelve un vector de pares< int, par: int, int >
// que funcionan como las reglas de compresion
vector<pair<int, pair<int, int>>>* solUno::Compress(LinkedList *l)
{
    list = l;
    vector<pair<int, pair<int, int>>> *reglas = new vector<pair<int, pair<int, int>>>();
    int regla = 28;
    if(list->size() == 0)
    {
        cout << "no hay elementos para comprimir."
        "Ejecuta addSequence antes que iterCompress" << endl;
        return reglas;
    }

    map<pair<int,int>, int> *m;
    map<pair<int,int>, int>::iterator BEEG;
    while(true)
    {
        m = fillMap();

        // ESTO NOS DICE CUAL ES EL PAR QUE MAS SE REPITE EN LA LISTA
        // (ESO SI, NO NECESARIAMENTE EL 1ER PAR REPETIDO)
        BEEG = max_element(m->begin(),m->end(),[]
        (const pair<pair<int,int>, int>& a, const pair<pair<int,int>, int>& b)->bool
        {return a.second < b.second;});
        pair<int, int> replace = BEEG->first;

        // cout << "Max is: " << BEEG->first.first << " " << BEEG->first.second << ", " << BEEG->second << endl;
        // cout << "Tenemos que reemplasar el par: " << replace.first << " " << replace.second<< endl;

        if(BEEG->second == 1) break;

        // Buscar y, al mismo tiempo, cambiar el par encontrado por la regla 28, 29, ..., n
        ParCompress(regla, replace);
        reglas->push_back(make_pair(regla++, replace));
        delete m;
    }
    delete m;
    return reglas;
}

map<pair<int,int>, int>* solUno::fillMap()
{
    map<pair<int,int>, int> *m = new map<pair<int,int>, int>();
    if(list->size() == 0)
    {
        cout << "no hay elementos para comprimir."
        "Ejecuta addSequence antes que iterCompress" << endl;
        delete m;
        return m;
    }

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
        itMap = m->find(pAux);

        if(itMap != m->end())
            itMap->second++;
        else
            m->insert(make_pair(pAux, 1));

        it++;
    }
    // auto itMap2 = m->begin();
    //
    // while(itMap2 != m->end())
    // {
    //     cout << itMap2->first.first << " " << itMap2->first.second << ", " << itMap2->second << endl;
    //     itMap2++;
    // }

    return m;
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
            // esto es para el extranio caso de que el par este al final de la lista
            // si ese fuera el caso, el while se queda en un loop infinito por temas
            // de la implementacion
            if(it.nodo()->next == it.end()) break;
        }
        it++;
    }
}