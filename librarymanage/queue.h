#ifndef QUEUE_H
#define QUEUE_H
#include "utility"
#include "The_doc_gia.h"
using namespace std;

struct node
{
    pair<int,int> ranges;
    node *next;
};

struct Queue
{
    node* Front;
    node* Rear;
    Queue() {
        Front = Rear = nullptr;
    }
    void push(pair<int,int>);
    void pop();
    pair<int,int> front();
    bool empty();
};

void Tao_Mang_The();
void taoMangTrungVi(int& index, int start, int end);


#endif // QUEUE_H
