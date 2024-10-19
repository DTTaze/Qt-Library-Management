#include "Mang_The_Ngau_Nhien.h"

void Queue::push(pair<int,int> x) {
    node* p = new node;
    p->ranges = x;
    p->next = nullptr;
    if (this->Front == nullptr) {
        this->Front = p;
    } else {
        this->Rear->next= p;
    }
    this->Rear = p;
    return;
}

void Queue::pop() {
    if( this->Front == nullptr ) {
        return;
    }
    node* p = this->Front;    // nut can xoa la nut dau
    this->Front = p->next;
    delete p;
    return;
}

pair<int,int> Queue::front() {
    if ( this->Front == nullptr ) return {-1,-1};
    return this->Front->ranges;
}

bool Queue::empty() {
    if ( this->Front == nullptr ) {
        return true;
    } else {
        return false;
    }
}

void Tao_Mang_The() {
    int index = 0;
    taoMangTrungVi(index, 1, 10000);
}

void taoMangTrungVi(int& index, int start, int end) {
    Queue ranges; // Queue dùng để duyệt các khoảng theo thứ tự hạng
    ranges.push({start, end}); // [a,b]

    while (!ranges.empty()) { // Lặp lại cho tới khi không còn khoảng nào
        auto range = ranges.front();
        ranges.pop();

        int s = range.first; // a
        int e = range.second; // b

        if (s > e) continue; // Nếu mà khoảng không hợp lệ thì bỏ qua

        int median = (s + e) / 2; // Tìm vị trí chính giữa
        Mang_Ma_The[index++] = median; // Thêm giá trị vào mảng
        ranges.push({s, median - 1}); // [a - 1, median]
        ranges.push({median + 1, e}); // [median + 1, b]
    }
}


