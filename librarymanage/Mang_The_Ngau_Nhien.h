#ifndef MANG_THE_NGAU_NHIEN_H
#define MANG_THE_NGAU_NHIEN_H
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


#endif // MANG_THE_NGAU_NHIEN_H
