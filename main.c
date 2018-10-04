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

    selection_sort(rows, counter);
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