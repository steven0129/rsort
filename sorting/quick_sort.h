#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include"type.h"

unsigned int partition (ROW*, unsigned int, unsigned int, int);
void quick_sort(ROW*, unsigned int, unsigned int, int);

void quick_sort(ROW* arr, unsigned int low, unsigned int high, int reverse) { 
    if (low < high) { 
        int pi = partition(arr, low, high, reverse); 
        quick_sort(arr, low, pi - 1, reverse);
        quick_sort(arr, pi + 1, high, reverse);
    }
}

unsigned int partition(ROW* arr, unsigned int low, unsigned int high, int reverse) { 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) {
        if(reverse) {
            if (arr[j].key >= arr[high].key) { 
                i++;    // increment index of smaller element 
                ROW temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        } else {
            if (arr[j].key <= arr[high].key) { 
                i++;    // increment index of smaller element 
                ROW temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    ROW temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp; 
    return (i + 1); 
}

#endif