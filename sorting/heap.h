#ifndef HEAP_H
#define HEAP_H
#include<limits.h>
#include"type.h"

ROW heap[100];
int heapSize;
/*Initialize Heap*/
void Init() {
    heapSize = 0;
    heap[0].key = -INT_MAX;
}
 
/*Insert an element into the heap */
void Insert(ROW element) {
    heapSize++;
    heap[heapSize] = element; /*Insert in the last place*/
    /*Adjust its position*/
    int now = heapSize;
    while (heap[now / 2].key > element.key) {
        heap[now] = heap[now / 2];
        now /= 2;
    }
    heap[now] = element;
}
 
ROW DeleteMin() {
    /* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased.
     Now heap[1] has to be filled. We put the last element in its place and see if it fits.
     If it does not fit, take minimum element among both its children and replaces parent with it.
     Again See if the last element fits in that place.*/
    ROW minElement, lastElement;
    int child, now;
    minElement = heap[1];
    lastElement = heap[heapSize--];
    /* now refers to the index at which we are now */
    for (now = 1; now * 2 <= heapSize; now = child) {
        /* child is the index of the element which is minimum among both the children */
        /* Indexes of children are i*2 and i*2 + 1*/
        child = now * 2;
        /*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one
         child */
        if (child != heapSize && heap[child + 1].key < heap[child].key) {
            child++;
        }
        /* To check if the last element fits ot not it suffices to check if the last element
         is less than the minimum element among both the children*/
        if (lastElement.key > heap[child].key) {
            heap[now] = heap[child];
        } else /* It fits there */
        {
            break;
        }
    }
    heap[now] = lastElement;
    return minElement;
}
#endif