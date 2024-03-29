#include "MaxHeap.h"

using namespace std;

MaxHeap::MaxHeap() {
    vect = new vector<pair<int, pair<int, int>>>();
    posiciones = new map<pair<int, int>, str>();
}

MaxHeap::~MaxHeap() {
    delete vect;
    delete posiciones;
}

void MaxHeap::Compress(LinkedList *l)
{
    list = l;
    int rule = 28;
    if(list->size() < 2)
    {
        cout
        << "no hay suficientes elementos para intentar comprimir, o "
        << "ejecutaste sDos primero que addSequence."
        << endl;
        return;
    }

    fillHeapAndMap(); // O(n*Logn) (se ejecuta solo 1 (UNA) vez)

    // HASTA AQUI, EL MAP, EL HEAP Y LOS PUNTEROS PREVOCURR Y NEXTOCURR DE LOS NODOS
    // DE LA LL ESTAN TODOS INICIADOS CORRECTAMENTE.
    // AHORA INICIA EL PROCESO DE COMPRESION REAL.

    // hasta que el par en la raiz del heap no sea igual a 1, continua comprimiendo
    pair<int, pair<int, int>> auxPair;
    itM maxInMap;
    while(true)
    {   // reviso en el heap cual es el par de mayor frecuencia
        auxPair = getMax();

        // si la frecuencia del par es igual a 1, termina la compresion
        if(auxPair.first == 1) break;

        // en el map, busco el par de mayor frecuencia
        maxInMap = getIndex(auxPair.second); // O(Logn)

        // utilizando los punteros en la struct del par (maxInMap)
        // actualizo los ptrs correspondientes
        // y comprimo el par
        compress_most_Freq(maxInMap, rule);
        rule++;
    }
}

void MaxHeap::fillHeapAndMap()
{   // creo un iterador de LL que apunta al 1er nodo de la lista
    Iterator it = list->begin(); 
    // creo un pair auxiliar para manejar los valores
    pair<int, int> pAux;
    while(it.hasNext())
    {   // se le inserta el nuevo (o repetido) par al heap,
        // junto a un puntero al 1er elemento del par
        pAux = make_pair(it.nodo()->n, it.nodo()->next->n);
        insert(pAux, it.nodo());
        it++;
    }
}

// comprime el par mas frecuente (el que esta en la raiz del heap)
void MaxHeap::compress_most_Freq(itM maxInMap, int rule)
{   // vayamos a la 1era ocurrencia del par
    // utilizando el puntero en el struct del map
    nodo *ref = maxInMap->second.first;

    ///* 1ero revisemos el par a la izquierda de la ocurrencia actual *///

    // mientras que aun haya ocurrencias del par (x, y) por comprimir, continua
    pair<int, int> pairHandler;
    while(true)
    {
        pairHandler = make_pair(ref->prev->n, ref->n);
        // aseguremonos de que el 1er valor del par izquierdo
        // no sea el valor de la "head" (-2) de la LL
        if(pairHandler.first != -2)
        {   // con el par izquierdo en mano (pairHandler)
            // busquemoslo en el map
            itM parLeft = posiciones->find(pairHandler);
            // con la posicion del par en el map en mano
            // actualizamos sus punteros
            prepair_ptrs_for_compression(ref->prev, parLeft);
            // y ahora debemos disminuir su frequencia
            updateFrequency(parLeft, -1);
        }

        ///* Ahora revisemos el par a la derecha de la ocurrencia actual *///

        // el proseso es igual al del par izquierdo
        // por lo que podemos reutilizar algunas de las
        // variables auxiliares que ya utilizamos para el par izquierdo
        pairHandler = make_pair(ref->next->n, ref->next->next->n);
        if(pairHandler.second != -2)
        {   // con el par derecho en mano (pairHandler)
            // busquemoslo en el map
            itM parRight = posiciones->find(pairHandler);
            // con la posicion del par en el map en mano
            // actualizamos sus punteros
            prepair_ptrs_for_compression(ref->next, parRight);
            // y ahora debemos disminuir su frequencia
            updateFrequency(parRight, -1);
        }
        // ahora hay que comprimir la 1era, 2da, etc... ocurrencia del par que mas se esta repitiendo
        ref = compressing_ocurr(ref, rule);

        maxInMap->second.first = ref;
        
        // si ya no hay mas ocurrencias del par, termina la compresion del par
        if(ref == nullptr) break;
    }
    
    // por ultimo, eliminemos el par resien comprimido del heap y del map
    delete_pair(maxInMap);
}

/*
 * actualiza los ptrs [prev/next]Ocurr y, si estamos en la 1era o ultima ocurrencia,
 * actualiza tambien los punteros de first/last de la struct del par en el map
 * de los nodos que se veran afectados por la compresion de la ocurrencia actual 
 * (es decir, los nodos a los lados de la ocurrencia)
 * 
 * Los nodos afectados dejaran de ser una ocurrencia de sus pares respectivos
 * y, posteriormente (despues de la ejecucion de este metodo),
 * a su par respectivo se le disminuira su frecuencia en 1
*/
void MaxHeap::prepair_ptrs_for_compression(nodo* nPtr, itM index)
{   // si el par no tiene frecuencia anterior, ni frecuencia siguiente,
    // entonces estamos con la unica frecuencia del par
    if(nPtr->prevOcurr != nullptr ||nPtr->nextOcurr != nullptr)
    {   // si no tienes una ocurrencia previa entonces eres la 1era ocurrencia
        if(nPtr->prevOcurr == nullptr)
        {
            index->second.first = nPtr->nextOcurr;
            nPtr->nextOcurr->prevOcurr = nullptr;
        }

        // si no tienes una ocurrencia siguiente entonces eres la ultima ocurrencia
        if(nPtr->nextOcurr == nullptr)
        {
            index->second.last = nPtr->prevOcurr;
            nPtr->prevOcurr->nextOcurr = nullptr;
        }

        // si tienes ocurrencia anterior y siguiente enotnces estas en medio de las ocurrencias
        if(nPtr->prevOcurr != nullptr && nPtr->nextOcurr != nullptr)
        {
            nPtr->prevOcurr->nextOcurr = nPtr->nextOcurr;
            nPtr->nextOcurr->prevOcurr = nPtr->prevOcurr;
        }
    }
    // como eres la unica ocurrencia del par entonces tu frecuencia pasara a ser 0
    // y el par saldra del heap y del map. Asi, desreferenciemos los punteros
    // de la struct en el map del par para evitar posibles problemas
    else index->second.first = index->second.first = nullptr;

    // y deja de apuntar a tus ocurrencias anterior y siguiente
    nPtr->prevOcurr = nPtr->nextOcurr = nullptr;

    /* Cementerio de comentarios */
    // los punteros del map deben estar apuntando
    // a la 1era ocurrencia del par, y a la ultima
    // ocurrencia del par.
    // Pero como este esta siendo un par al que se le esta disminuyendo
    // su frecuencia, significa que va a dejar de ser un par
    // de ese par (si me explico)
    //
    // // si el par NO tiene ocurrencia ANTERIOR, significa que estamos
    // // en la 1era ocurrencia del par. Por lo tanto, la nueva 1era
    // // ocurrencia sera la 2da ocurrencia del par
    // if(nPtr->prevOcurr == nullptr) index->second.first = nPtr->nextOcurr;
    // //si el par SI tiene ocurrencia enterior, estamos en medio de las
    // // ocurrencias del par. Por lo tanto, no cambiamos el ptr de 1er ocurrencia
    // // de este par
    // else /* nada (LA CARACOLA MAGICA HA HABLADO!! alalalalalalalalalala!!!)*/;
    //
    // // revisamos lo mismo que lo anterior, pero para el caso de que
    // // la ocurrencia actual NO tenga SIGUIENTE ocurrencia
    // if(nPtr->nextOcurr == nullptr) index->second.last = nPtr->prevOcurr;
    // else /* nada */;
    //
    // /**references
    //  * ahora actualizemos los ptrs [next/prev]Ocurr del nodo.
    //  * prevOcurr esta apuntando a la ocurrencia siguiente.
    //  * Pero como este par prontamente dejara de existir, tenemos
    //  * que deslinkearlo de la cadena de ocurrencias
    //  */
    //
    // // si el par no tiene ocurrencia anterior, no hacemos nada
    // if(nPtr->prevOcurr == nullptr) /* nada */;
    // // si el par SI tiene ocurrencia ANTERIOR, estamos en medio de las
    // // ocurrencias del par. Por lo tanto, tenemos que actualizar el ptr
    // // de la ocurrencia anterior de la ocurrencia siguiente de la ocurrencia actual para que
    // // apunte a la ocurrencia anterior de la ocurrencia actual (uno, o lo dibuja, o se pierde)
    // else nPtr->nextOcurr->prevOcurr = nPtr->prevOcurr;
    //
    // // revisamos lo mismo que lo anterior
    // if(nPtr->nextOcurr == nullptr) /* nada */;
    // // Pero para el caso de que
    // // la ocurrencia actual SI tenga SIGUIENTE ocurrencia
    // else nPtr->prevOcurr->nextOcurr = nPtr->nextOcurr;
}

/**
 * Comprime la ocurrencia que esta lo mas a la izquierda
 * de las ocurrencias del par mas repetido
 * Revise un ptr a la ocurrencia a comprimir,
 * la regla de compresion y
 * devuelve un ptr a la siguiente ocurrencia del par
 * (si no tiene siguiente ocurrencia, devuelve un nullptr)
*/
nodo* MaxHeap::compressing_ocurr(nodo* nPtr, int rule)
{   // el proceso de comprecion de ocurrencias consiste en:

    // 1.- guardar el ptr a la siguiente ocurrencia del par
    nodo *auxN = nPtr->nextOcurr;
    // (este sera retornado al final del metodo)

    // 2.- desreferenciar a la ocurrencia actual de su ocurrencia siguiente
    // y a la ocurrencia siguiente de su ocurrencia anterior (que es la actual)
    if(auxN != nullptr)
    {
        nPtr->nextOcurr = nullptr;
        auxN->prevOcurr = nullptr;
    }

    // 3.- eliminar el nodo siguiente 
    /*
     * para detectar errores, exijamos tambien una condicion:
     * los ptrs de [next/prev]Ocurr del nodo siguiente deben de ser nullptrs.
     * Si estos no son nullptrs, entonces hubo un problema en pasos anteriores
     * (muy probablemente en metodos anteriores de manejo de punteros)
    */
    nodo *auxDeleter = nPtr->next;
    if(auxDeleter->prevOcurr == nullptr
    && auxDeleter->nextOcurr == nullptr)
    {
        list->popAt(auxDeleter);
    }
    else
    {
        cout
        << "hubo un problema en 'compressing_ocurr'"
        << "con el par " << nPtr->n << " " << auxDeleter->n
        << "rule: " << rule << endl;
        return auxN;
    }
    
    // 4.- entregarle al nodo "nPtr" la regla actual
    nPtr->n = rule;
    // nuevos pares que no estan en le heap/map, se crearon.
    // Los pares (valor nodo anterior, rule) y (rule, valor nodo siguiente)

    // 5.- agregar al heap y al map los nuevos pares
    // (teniendo cuidado de que estos pares nuevos no sean la head o la tail de la LL)
    if(nPtr->prev->prev != nullptr) insert(make_pair(nPtr->prev->n, nPtr->n), nPtr->prev);
    // else cout << nPtr->prev->n << " " << nPtr->n << endl;
    
    if(nPtr->next->next != nullptr) insert(make_pair(nPtr->n, nPtr->next->n), nPtr);
    // else cout << nPtr->n << " " << nPtr->next->n << endl;
    return auxN;
}

void MaxHeap::insert(std::pair<int, int> pair, nodo* nPtr) {
    // llamo a un iterador de map para decirme si el par esta, o no
    itM index = getIndex(pair);
    // si el par no es encontrado, entonces hay que agregarlo
    if (index == posiciones->end()) {
        auto entry = make_pair(1, pair);
        vect->push_back(entry);

        // creo la estructura a insertar en el map junto al par "pair"
        str str_aux;
        str_aux.first = str_aux.last = nPtr;
        str_aux.heapIndex = vect->size() - 1;

        posiciones->insert(make_pair(pair, str_aux));
        shiftUp(vect->size() - 1);
    } else {
        // si el par ya se encuentra en el heap/map
        // actualizo:
        // los punteros de nextOcurr/prevOcurr de los nodos de la LL con par repetido
        // y el puntero de la ultima ocurrencia de este par
        updatePtrsForInsert(nPtr, index);
        // y la frecuencia del par
        updateFrequency(index, 1);
    }
}

void MaxHeap::updatePtrsForInsert(nodo* nPtr, itM index)
{   // le entrego al par actual un puntero a su ocurrencia anterior
    // (esta ocurrencia anterior es la ultima ocurrencia que fue guardada en
    // la struct del par en el map)
    nPtr->prevOcurr = index->second.last;
    // al penúltimo par le entrego su siguiente ocurrencia
    nPtr->prevOcurr->nextOcurr = nPtr;
    // la última ocurrencia del par termina siendo guardada en la stru del par en el map
    index->second.last = nPtr;
}

itM MaxHeap::getIndex(std::pair<int, int> pair) {
    auto it = posiciones->find(pair);
    return it;
}

void MaxHeap::updateIndex(std::pair<int, int> pair, int newIndex) {
    auto it = posiciones->find(pair);
    if (it != posiciones->end())
        it->second.heapIndex = newIndex;
}

void MaxHeap::swap(int i1, int i2) {
    auto aux = vect->at(i1);
    vect->at(i1) = vect->at(i2);
    vect->at(i2) = aux;
    auto swappedPair = aux.second;
    updateIndex(swappedPair, i2);
    swappedPair = vect->at(i1).second;
    updateIndex(swappedPair, i1);
}

pair<int, pair<int, int>> MaxHeap::getMax() {
    return vect->at(0);
}

pair<int, pair<int, int>> MaxHeap::extractMax() {
    auto max = vect->at(0);    
    swap(0, vect->size() - 1);
    vect->pop_back();
    posiciones->erase(max.second);
    shiftDown(0);
    return max;
}

void MaxHeap::shiftDown(int index) {
    int size = vect->size();
    if (size > 1) {        
        int n = vect->at(index).first; // la frecuencia del par que esta en el indice "index"
        int leftIndex = left(index);
        int rightIndex = right(index);
        if (leftIndex >= size)
            return;
        int l = vect->at(leftIndex).first;
        int r = -1;
        if (rightIndex < size)
            r = vect->at(rightIndex).first;
        
        if (n < l) // izquierda es mayor que parent
            if (l > r) {
                int li = left(index);
                swap(index, li);
                shiftDown(li);
                return;
            }
        if (n < r) {
            int ri = right(index);
            swap(index, ri);
            shiftDown(ri);
            return;
        }
    }
}

void MaxHeap::shiftUp(int index) {
    if (vect->size() > 1) {
        int n = vect->at(index).first;
        int p = vect->at(parent(index)).first;
        if (n > p) {
            int pi = parent(index);
            swap(index, pi);
            shiftUp(pi);
            return;
        }
    }
}

void MaxHeap::updateFrequency(itM index, int change) {
    /// buscar
    if (index == posiciones->end())
        return;

    vect->at(index->second.heapIndex).first += change;
    if (vect->at(index->second.heapIndex).first <= 0) {
        delete_pair(index);
    }
    else if (change < 0) {
        shiftDown(index->second.heapIndex);
    } else {
        shiftUp(index->second.heapIndex);
    }
}

void MaxHeap::delete_pair(itM index) {
    if (index == posiciones->end())
        return;
    if (index->second.heapIndex == vect->size() - 1) {
        vect->pop_back();
    } else {
        int prevIndex = index->second.heapIndex;
        swap(index->second.heapIndex, vect->size() - 1);
        vect->pop_back();
        shiftDown(prevIndex);
    }
    // esto se esta ejecutando siempre. Pero, que sasi si tengo 3 pares 
    posiciones->erase(index->first);
}

void MaxHeap::printHeap() {
    cout << "heap = [ ";
    auto it_vect = vect->begin();
    while(it_vect < vect->end()) {
        cout << "(" << it_vect->first << ", {" << it_vect->second.first << ", " << it_vect->second.second << "}), ";
        it_vect++;
    }
    cout << "]" << endl;
}

void MaxHeap::printIndexes() {
    cout << "indexes = [ ";
    auto it_map = posiciones->begin();
    while(it_map != posiciones->end()) {
        cout << "({" << it_map->first.first << ", " << it_map->first.second << "}, " << it_map->second.heapIndex << "), ";
        it_map++;
    }
    cout << "]" << endl;
}

std::vector<std::pair<int, std::pair<int, int>>>::iterator  MaxHeap::begin(){
    auto it = this->vect->begin();
    return it;
}

std::vector<std::pair<int, std::pair<int, int>>>::iterator  MaxHeap::end(){
    auto it = this->vect->end();
    return it;
}

int MaxHeap::parent(int index){
    return (index - 1) / 2;
}

int MaxHeap::left(int index){
    return (index*2) + 1;
}

int MaxHeap::right(int index){
    return (index*2) + 2;
} 

// revisa los punteros [next/prev]Ocurr de un par entregandole su str que esta en el map
void MaxHeap::checkPointers(str stru) {
    cout << vect->at(stru.heapIndex).first << endl;
    auto first = stru.first;
    auto last = stru.last;
    while (first != last) {
        cout << "("<<(first->prev == nullptr ? - 1 :first->prev->n) << " " << first->n << " " << first->next->n << " " << (first->next->next == nullptr ? -1 :first->next->next->n) << "), ";
        first = first->nextOcurr;
    }
    cout << "("<<(last->prev == nullptr ? - 1 :last->prev->n) << " " << last->n << " " << last->next->n << " " << (last->next->next == nullptr ? -1 :last->next->next->n) << "), ";
    cout <<  endl;
}