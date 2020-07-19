#include "MaxHeap.h"

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
    fillHeap();

    return;
}

void MaxHeap::fillHeap()
{
    //////////iteracion en la linked list//////////
    // creo un puntero nodo que apunta al 1er nodo de la lista
    Iterator it = list->begin();
    // creo un pair auxiliar para manejar los valores
    pair<int, int> pAux;
    // cuando la tail de la LL se alcance entonces no quedaran mas
    // valores en la LL por los cuales iterar
    while(it.nodo()->next != it.end())
    {
        // se le inserta el nuevo (o repetido) par al heap,
        // junto a un puntero al 1er elemento del par
        pAux = make_pair(it.nodo()->n, it.nodo()->next->n);

        insert(pAux, it.nodo());
        it++;
    }
}

map<pair<int, int>, str>::iterator MaxHeap::getIndex(std::pair<int, int> pair) {
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
        int n = vect->at(index).first;
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

void MaxHeap::updatePtrs(nodo* nPtr, map<pair<int, int>, str>::iterator index)
{
    // la anterior ocurrencia del par
    nPtr->prevOcurr = index->second.first;
    // la siguiente ocurrencia del penultimo par
    nPtr->prevOcurr->nextOcurr = nPtr;
    // la ultima ocurrencia del par (el guardado en la str del map)
    index->second.last = nPtr;
}

void MaxHeap::insert(std::pair<int, int> pair, nodo* nPtr) {
    // llamo a un iterador de map para decirme si el par esta, o no
    auto index = getIndex(pair);
    // si el par no es encontrado, entonces hay que agregarlo
    if (index == posiciones->end()) {
        auto entry = make_pair(1, pair);
        vect->push_back(entry);

        // creo la estructura a incertar en el map junto al par "pair"
        str str_aux;
        str_aux.first = str_aux.last = nPtr;
        str_aux.heapIndex = vect->size() - 1;

        posiciones->insert(make_pair(pair, str_aux));
        shiftUp(vect->size() - 1);
    } else {
        // actualizo:
        // los punteros de nextOcurr/prevOcurr de los nodos de la LL con par repetido
        // y el puntero de la ultima ocurrencia de este par
        updatePtrs(nPtr, index);
        // y la frecuencia del par
        updateFrequency(index, 1);
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

void MaxHeap::updateFrequency(map<pair<int, int>, str>::iterator index, int change) {
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

void MaxHeap::delete_pair(map<pair<int, int>, str>::iterator index) {
    if (index == posiciones->end())
        return;
    if (index->second.heapIndex == vect->size() - 1) {
        vect->pop_back();
    } else {
        swap(index->second.heapIndex, vect->size() - 1);
        vect->pop_back();
        shiftDown(index->second.heapIndex);
    }
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