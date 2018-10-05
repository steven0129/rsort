#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
#include"type.h"

void bubble_sort(ROW* array, int n) {
    ROW temp;
    for(int i=n-1; i > 0; i--) {
        for(int j=0; j <= i-1; j++) {
            if(array[j].key > array[j + 1].key) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

#endif