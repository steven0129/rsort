#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#include"type.h"

void selection_sort(ROW* array, int n, int reverse) {
    ROW temp;
    for(int i=0; i<n-1; i++) {
        int min = i;
        for(int j=i+1; j<n; j++) {
            if(reverse) {
                if(array[j].key > array[min].key)
                    min = j;
            } else {
                if(array[j].key < array[min].key)
                    min = j;
            }
            
        }

        temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

#endif