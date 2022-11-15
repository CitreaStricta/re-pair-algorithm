#include "iterator.h"
#include <iostream>

using namespace std;

Iterator::Iterator(struct nodo* begin, struct nodo* end) {
    if(!begin) begin = end;
    this->_begin = begin;
    this->_end = end;
    _nodo = this->_begin;
}

Iterator::~Iterator(){}

Iterator& Iterator::operator++(int){
    if (_nodo->next != nullptr)
        _nodo = _nodo->next;
    return *this;
}

Iterator& Iterator::operator--(int){
    if (this->_nodo->prev != nullptr)
        this->_nodo = this->_nodo->prev;
    return *this;
}

bool Iterator::hasNext(){
    if (_nodo->next != _end)
        return true;
    return false;
}

void Iterator::goToStart()
{
    _nodo = _begin;
}

nodo* Iterator::nodo() {
    return _nodo;
}

nodo* Iterator::begin() {
    return _begin;
}

nodo* Iterator::end() {
    return _end;
}
