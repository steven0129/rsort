#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include"type.h"

void insertion_sort(ROW* array, int n) {
    ROW temp;
    int j;
    for(int i=1; i<n; i++) {
        temp = array[i];
        j = i-1;

        while(j>=0 && array[j].key > temp.key) {
            array[j+1] = array[j];
            j--;
        }

        array[j+1] = temp;
    }
}

#endif