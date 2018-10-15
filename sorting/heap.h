#ifndef HEAP_H
#define HEAP_H
#include"type.h"

void restoreDown(ROW*, int, int, int);
void buildHeap(ROW*, int, int);

void restoreDown(ROW* arr, int len, int idx, int k) {
    // child array to store indexes of all the children of given node 
    int child[k + 1];
    while(1) {
        // child[i] = -1 if no children
        for(int i=1; i<=k; i++)
            child[i] = ((k * idx + i) < len) ? (k * idx + i) : -1; 
    
        int max_child = -1, max_child_idx;
        for(int i=1; i<=k; i++) {
            if(child[i] != -1 && arr[child[i]].key > max_child) {
                max_child_idx = child[i];
                max_child = arr[child[i]].key;
            }
        }

        if(max_child == -1) break;
        if(arr[idx].key < arr[max_child_idx].key) {
            ROW tmp = arr[idx];
            arr[idx] = arr[max_child_idx];
            arr[max_child_idx] = tmp;
        }

        idx = max_child_idx;
    }
}

void buildHeap(ROW* arr, int n, int k) {
    for(int i = (n-1) / k; i>=0; i--)
        restoreDown(arr, n, i, k);
}

#endif