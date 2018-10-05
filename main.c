#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#include<string.h>
#define BUFFER_SIZE 50000

typedef struct {
    int idx;
    int key;
    wchar_t* data;
} ROW;

wchar_t* wcscat_m(wchar_t*, wchar_t*);
void bubble_sort(ROW*, int);
void insertion_sort(ROW*, int);
void selection_sort(ROW*, int);
void merge_sort(ROW*, int, int);
void merge(ROW*, int, int, int);
void heap_sort(ROW*, int);
void heapify(ROW*, int, int);
int partition (ROW*, int, int);
void quick_sort(ROW*, int, int);
int get_signs_index(char);
int hex2dec(char*);

int main(int argc, char *argv[]) {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    FILE* inFile;
    if(argc > 1) {
        inFile = fopen(argv[argc - 1], "r");
    } else {
        inFile = stdin;
    }

    if(inFile == NULL) {
        printf("No such file or could not open it.\n");
        exit(1);
    }
    
    int debug = 0;
    int counter = 0;
    ROW rows[400000];
    wchar_t delimeter[] = L"\n";
    wchar_t* keyPat = L"@T";
    wchar_t* end = L"@GAISRec:";
    wchar_t line[BUFFER_SIZE];

    while(fgetws(line, sizeof(line), inFile) != NULL) {
        wchar_t* tmp = (wchar_t*)malloc(sizeof(wchar_t) * ((int)wcslen(line) + 1));
        wchar_t* str;
        wcscpy(tmp, line);
        str = wcscat_m(str, tmp);
        rows[counter].idx = counter;

        while(fgetws(line, sizeof(line), inFile) != NULL) {
            size_t newSize = sizeof(wchar_t) * ((int)wcslen(line) + 1);
            tmp = (wchar_t*)malloc(newSize);
            wcscpy(tmp, line);

            if(wcsstr(tmp, end)) {
                rows[counter].data = (wchar_t*)malloc(sizeof(wchar_t) * ((int)wcslen(str) + 1));
                wcscpy(rows[counter].data, str);
                counter++;
                wcscpy(str, L"");
                break;
            }

            str = wcscat_m(str, tmp);
        }
    }

    for(int i=0; i < counter; i++) {
        wchar_t* buffer;
        char *ptr;
        char hex[5];
        wchar_t* data = (wchar_t*)malloc(sizeof(wchar_t) * ((int)wcslen(rows[i].data) + 1));
        wcscpy(data, rows[i].data);
        wchar_t* result = wcsstr(data, keyPat);
        result = wcstok(result, L"\n", &buffer);
        result = wcstok(result, L":", &buffer);
        result = wcstok(NULL, L":", &buffer);
        sprintf(hex, "%04x", result[0]);
        rows[i].key = hex2dec(hex);
    }

    quick_sort(rows, 0, counter - 1);
    for(int i = 0; i < counter; i++) {
        printf("%ls", rows[i].data);
    }
}

wchar_t* wcscat_m(wchar_t* str1, wchar_t* str2) {
    int len = 0;
    wchar_t* s;

    if(str1 != NULL)
        len = sizeof(wchar_t) * ((int)wcslen(str1) + 1);

    len += sizeof(wchar_t) * ((int)wcslen(str2) + 1);
    s = realloc(str1, len);
    wcscat(s, str2);
    return s;
}

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

void selection_sort(ROW* array, int n) {
    ROW temp;
    for(int i=0; i<n-1; i++) {
        int min = i;
        for(int j=i+1; j<n; j++) 
            if(array[j].key < array[min].key)
                min = j;

        temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

void merge_sort(ROW* array, int i, int j) {
    int mid;
    if(i<j) {
        mid = (i + j)/2;
        merge_sort(array, i, mid);
        merge_sort(array, mid+1, j);
        merge(array, i, mid, j);
    }
}

void merge(ROW* arr, int l, int m, int r) {
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    ROW L[n1], R[n2]; 

    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
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
}

void heap_sort(ROW* arr, int n) { 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end
        ROW temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
    } 
}

void heapify(ROW* arr, int n, int i) { 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l].key > arr[largest].key) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r].key > arr[largest].key) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        ROW temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
}

void quick_sort(ROW* arr, int low, int high) { 
    if (low < high) { 
        int pi = partition(arr, low, high); 
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
} 

int partition (ROW* arr, int low, int high) { 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) { 
        if (arr[j].key <= arr[high].key) { 
            i++;    // increment index of smaller element 
            ROW temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    ROW temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp; 
    return (i + 1); 
}

int hex2dec(char* src) {
    int sum = 0;
    int t = 1;
    int i, len;
    
    len = strlen(src);
    for(i = len-1; i>=0; i--) {
        sum += t * get_signs_index(*(src + i));
        t *= 16;
    }

    return sum;
}

int get_signs_index(char ch) {
    if(ch >= '0' && ch <= '9') {
        return ch - '0';
    }

    if(ch >= 'A' && ch <='F') {
        return ch - 'A' + 10;
    }

    if(ch >= 'a' && ch <='f') {
        return ch - 'a' + 10;
    }

    return -1;
}