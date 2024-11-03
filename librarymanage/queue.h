#ifndef QUEUE_H
#define QUEUE_H
#include "utility"
#include "The_doc_gia.h"
using namespace std;

template<typename T>
struct node
{
    T data;
    node *next = nullptr;
    node() {}
    node(T val) : data(val), next(nullptr) {}
};

template<typename T>
struct Queue
{
    node<T>* Front = nullptr;
    node<T>* Rear = nullptr;
    Queue() : Front(nullptr), Rear(nullptr) {}
    void push(T value);
    void pop();
    T front();
    bool empty();
    void clear();
    Queue<T> copy();
};

template<typename T>
void Queue<T>::push(T value) {
    node<T>* p = new node<T>(value);
    if (this->Front == nullptr) {
        this->Front = p;
    } else {
        this->Rear->next= p;
    }
    this->Rear = p;
}

template<typename T>
void Queue<T>::pop() {
    if( this->Front == nullptr ) {
        return;
    }
    node<T>* p = this->Front;    // nut can xoa la nut dau
    this->Front = p->next;
    if (this->Front == nullptr) { // Nếu hàng đợi trống sau khi xóa
        this->Rear = nullptr;
    }
    delete p;
}

template<typename T>
T Queue<T>::front() {
    if ( this->Front == nullptr ) throw runtime_error("Queue is empty");;
    return this->Front->data;
}

template<typename T>
bool Queue<T>::empty() {
    return this->Front == nullptr;
}

template<typename T>
void Queue<T>::clear() {
    while (this->Front != nullptr) {
        node<T>* temp = this->Front;
        this->Front = this->Front->next;
        delete temp;
    }
    this->Rear = nullptr;  // Đảm bảo Rear cũng là nullptr sau khi xóa
}

template<typename T>
Queue<T> Queue<T>::copy() {
    Queue<T> newQueue;
    node<T>* current = this->Front;
    while (current != nullptr) {
        newQueue.push(current->data);
        current = current->next;
    }
    return newQueue;
}

#endif // QUEUE_H
