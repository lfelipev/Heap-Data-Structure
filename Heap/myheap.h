#ifndef MYHEAP_H
#define MYHEAP_H
#include<iostream>
#include "HeapADT.h"

using namespace std;

template <typename E> class myHeap : public HeapADT<E> {
private:
    E *content;
    int maxsize;
    int n;
    void helper(int pos) {
        while(!isLeaf(pos)) {
            int l = left(pos);
            int r = righ(pos);
            if ((r < n) && (content[r] <= content[l])) {
                l = r;
            }
            if (content[pos] <= content[l]) {
                return;
            }
            swap(content, pos, l);
            pos = l;
        }
    }
public:
    myHeap(E *h, int sz, int elements) {
        content = h; //ponteiro para o vetor da heap
        maxsize = sz; //tamanho maximo da heap
        n = elements; //quantidade de elementos da heap
        buildMaxHeap();
    }

    int size() const {
        return n;
    }

    bool isLeaf(int pos) const{
        return ((pos > n/2) && (pos < n));
    }

    int left(int pos) const {
        return 2*(pos+1);
    }

    int righ(int pos) const {
        return (2*(pos+1)) +1;
    }
    int parent(int pos) const {
        return (pos+1)/2;
    }
    void buildMaxHeap() {
        for (int i = n/2; i >= 0; --i) {
            helper(i);
        }
    }
    void insert(const E& it) {
        if (n > maxsize) {
            cout << "A Heap está cheia!" << endl;
        }
        else {
            int current = n++;
            content[current] = it;
            while ((current != 0) && content[current] <= content[parent(current)]){
                swap(content, current, parent(current));
                current = parent(current);
            }
        }
    }
    E removefirst() {
        if (n < 0) {
            cout << "A Heap está vazia!" << endl;
        }
        else {
            swap(content, 0, --n);
            if(n != 0) {
               helper(0);
            }
            return content[n];
        }
    }
    E remove(int pos) {
        if (pos <= 0 && pos > n) {
            cout << "Escolha outra posição!" << endl;
        }
        else {
            if (pos == n) {
                --n;
            }
            else {
                swap(content, pos, --n);
                while (pos != 0 && content[pos] <= content[parent(pos)]) {
                    swap(content, pos, parent(pos));
                }
                if(n != 0) {
                    helper(pos);
                }
            }
        }
        return content[n];
    }
};

#endif // MYHEAP_H
