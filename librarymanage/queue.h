#ifndef QUEUE_H
#define QUEUE_H
#include "utility"
#include "The_doc_gia.h"
using namespace std;

template<typename T>
struct node
{
    T data;
    node *next;
    node() {}
    node(T val) : data(val), next(nullptr) {}
};

template<typename T>
struct Queue
{
    node<T>* Front;
    node<T>* Rear;
    Queue() {
        Front = Rear = nullptr;
    }
    void push(T value);
    void pop();
    T front();
    bool empty();
};

template<typename T>
void Queue<T>::push(T value) {
    node<T>* p = new node<T>();
    p->data = value;
    p->next = nullptr;
    if (this->Front == nullptr) {
        this->Front = p;
    } else {
        this->Rear->next= p;
    }
    this->Rear = p;
    return;
}

template<typename T>
void Queue<T>::pop() {
    if( this->Front == nullptr ) {
        return;
    }
    node<T>* p = this->Front;    // nut can xoa la nut dau
    this->Front = p->next;
    delete p;
    return;
}

template<typename T>
T Queue<T>::front() {
    if ( this->Front == nullptr ) throw runtime_error("Queue is empty");;
    return this->Front->data;
}

template<typename T>
bool Queue<T>::empty() {
    if ( this->Front == nullptr ) {
        return true;
    } else {
        return false;
    }
}

#endif // QUEUE_H
