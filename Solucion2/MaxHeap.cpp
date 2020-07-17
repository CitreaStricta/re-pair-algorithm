#include "MaxHeap.h"

MaxHeap::MaxHeap() {
    this->_map = new map<pair<int, int>, HeapNode*>();
}

MaxHeap::~MaxHeap() {
    delete first;
    delete _map;
}

void MaxHeap::insertItem(std::pair<int, int> pair, int* address) {
    if (this->_size == 0) {
        auto heapNode = new HeapNode(pair, address);
        this->_map->insert({pair, heapNode});
        this->first = heapNode;
        this->last = heapNode;
    } else {
        auto it = this->_map->find(pair);
        if (it == _map->end()) {
            auto heapNode = new HeapNode(pair, address);
            if (this->last->left != nullptr)
                this->last = this->last->parent->left;
            this->last->insert(heapNode);
            this->_map->insert(make_pair(pair, heapNode));
        } else {
            it->second->increaseFrequency(address);
        }
    }
    this->_size++;
}

void MaxHeap::deleteItem(std::pair<int, int> pair) {
    auto it = this->_map->find(pair);
    if (it != _map->end()) {
        HeapNode* ultimo;
        if (this->last->left != nullptr) {
            ultimo = this->last->left;
            this->last = this->last->parent;
            this->last->left = nullptr;
        } else {
            ultimo = this->last;
            this->last = this->last->parent;
        }
        ultimo->swap(it->second);
        delete ultimo;
        it->second->shiftDown();
    }
}