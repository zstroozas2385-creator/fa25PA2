
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    bool lessAt(int i, int j, int weightArr[]) {
        int li = data[i], lj = data[j];
        if (weightArr[li] != weightArr[lj]) return weightArr[li] < weightArr[lj];
        return li < lj;
    }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size >= 64) {
            cerr << "Heap overflow.\n";
            exit(1);
        }
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) {
            cerr << "Pop from empty heap.\n";
            exit(1);
        }
        int ret = data[0];
        size--;
        if (size > 0) {
            data[0] = data[size];
            downheap(0, weightArr);
        }
        return ret;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (lessAt(pos, parent, weightArr)) {
                int tmp = data[pos];
                data[pos] = data[parent];
                data[parent] = tmp;
                pos = parent;
            } else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int left  = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;

            if (left < size && lessAt(left, smallest, weightArr))  smallest = left;
            if (right < size && lessAt(right, smallest, weightArr)) smallest = right;

            if (smallest != pos) {
                int tmp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = tmp;
                pos = smallest;
            } else {
                break;
            }
        }
    }
};

#endif