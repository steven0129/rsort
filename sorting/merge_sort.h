#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include<wchar.h>
#include"type.h"
void merge_sort(ROW*, int, int, int);
void merge(ROW*, int, int, int, int);
void mergeFiles(FILE*, int, int);

void merge_sort(ROW* array, int left, int right, int reverse) {
    int mid;
    if(left<right) {
        mid = left + (right - left)/2;
        merge_sort(array, left, mid, reverse);
        merge_sort(array, mid+1, right, reverse);
        merge(array, left, mid, right, reverse);
    }
}

void merge(ROW* arr, int l, int m, int r, int reverse) {
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    ROW* L = malloc(sizeof(ROW) * n1);
    ROW* R = malloc(sizeof(ROW) * n2); 

    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    {
        if(reverse) {
            if (L[i].key >= R[j].key) 
            { 
                arr[k] = L[i]; 
                i++; 
            } 
            else
            { 
                arr[k] = R[j]; 
                j++; 
            }
        } else {
            if (L[i].key <= R[j].key) 
            { 
                arr[k] = L[i]; 
                i++; 
            } 
            else
            { 
                arr[k] = R[j]; 
                j++; 
            } 
        }
        
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    }

    free(L);
    free(R);
}

void mergeFiles(FILE* outFile, int partition_size, int k_ways) {
    
}

#endif