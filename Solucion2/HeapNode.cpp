#include "HeapNode.h"

HeapNode::HeapNode(std::pair<int, int> pair, int* address) {
    this->_pair = pair;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->first = address;
    this->last = nullptr;
}

HeapNode::~HeapNode() {
    delete left;
    delete right;
}

void HeapNode::swap(HeapNode* node) {
    int tempFreq = node->frequency;
    auto tempPair = node->_pair;
    node->frequency = this->frequency;
    node->_pair = this->_pair;
    this->frequency = tempFreq;
    this->_pair = tempPair;
}

void HeapNode::shiftUp() {
    if (this->frequency > this->parent->frequency) {
        this->swap(this->parent);
        this->parent->shiftUp();
    }
}

void HeapNode::shiftDown() {
    if (this->frequency < this->left->frequency) 
        if (this->left->frequency > this->right->frequency) {
            this->swap(this->left);
            this->left->shiftDown(); 
            return;       
        }
    if (this->frequency < this->right->frequency) {
        this->swap(this->right);
        this->right->shiftDown();
        return;
    }    
}

void HeapNode::insert(HeapNode* node) {
    if (this->left != nullptr and this->right != nullptr)
        return;
    else {
        if (this->left == nullptr)
            this->left = node;
        else
            this->right = node;
        node->parent = this;
    }
}

void HeapNode::increaseFrequency(int* address) {
    this->last = address;
    this->frequency++;
    this->shiftUp();
}