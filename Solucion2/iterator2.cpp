#include "iterator2.h"
#include <iostream>

using namespace std;

Iterator2::Iterator2(struct nodo2* begin, struct nodo2* end) {
    if(!begin) begin = end;
    this->_begin = begin;
    this->_end = end;
    _nodo = this->_begin;
}

Iterator2::~Iterator2(){}

Iterator2& Iterator2::operator++(int){
    if (_nodo->next != nullptr)
        _nodo = _nodo->next;
    return *this;
}

Iterator2& Iterator2::operator--(int){
    if (this->_nodo->prev != nullptr)
        this->_nodo = this->_nodo->prev;
    return *this;
}

void Iterator2::goToStart()
{
    _nodo = _begin;
}

nodo2* Iterator2::nodo() {
    return this->_nodo;
}

nodo2* Iterator2::begin() {
    return _begin;
}

nodo2* Iterator2::end() {
    return _end;
}
