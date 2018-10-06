#ifndef HEAP_SORT_H
#define HEAP_SORT_H
#include"type.h"

void heap_sort(ROW*, int, int);
void heapify(ROW*, int, int, int);

void heap_sort(ROW* arr, int n, int reverse) { 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i, reverse); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end
        ROW temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0, reverse); 
    } 
}

void heapify(ROW* arr, int n, int i, int reverse) { 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    if(reverse) {
        if (l < n && arr[l].key < arr[largest].key) 
            largest = l; 
    
        if (r < n && arr[r].key < arr[largest].key) 
            largest = r; 
    } else {
        if (l < n && arr[l].key > arr[largest].key) 
            largest = l; 
    
        if (r < n && arr[r].key > arr[largest].key) 
            largest = r; 
    }
    
  
    // If largest is not root 
    if (largest != i) 
    { 
        ROW temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest, reverse); 
    } 
}

#endif