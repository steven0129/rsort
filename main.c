#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#include"number.h"
#include"bubble_sort.h"
#include"insertion_sort.h"
#include"selection_sort.h"
#include"merge_sort.h"
#include"heap_sort.h"
#include"quick_sort.h"
#include"type.h"
#define BUFFER_SIZE 50000

wchar_t* wcscat_m(wchar_t*, wchar_t*);

int main(int argc, char *argv[]) {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    FILE* inFile;
    if(argc > 1)
        inFile = fopen(argv[argc - 1], "r");
    else
        inFile = stdin;

    if(inFile == NULL) {
        printf("No such file or could not open it.\n");
        exit(1);
    }
    
    int counter = 0;
    char hex[5];
    ROW rows[400000];
    wchar_t delimeter[] = L"\n";
    wchar_t* keyPat = L"@T";
    wchar_t* end = L"@GAISRec:";
    wchar_t line[BUFFER_SIZE];
    wchar_t* buffer;

    while(fgetws(line, sizeof(line), inFile) != NULL) {
        buffer = wcscat_m(buffer, line);
        rows[counter].idx = counter;

        while(fgetws(line, sizeof(line), inFile) != NULL) {
            if(wcsstr(line, end)) {
                rows[counter].data = (wchar_t*)malloc(sizeof(wchar_t) * ((int)wcslen(buffer) + 1));
                wcscpy(rows[counter].data, buffer);
                counter++;
                wcscpy(buffer, L"");
                break;
            }

            buffer = wcscat_m(buffer, line);
        }
    }

    for(int i=0; i < counter; i++) {
        wchar_t* data = (wchar_t*)malloc(sizeof(wchar_t) * ((int)wcslen(rows[i].data) + 1));
        wcscpy(data, rows[i].data);
        data = wcsstr(data, keyPat);
        data = wcstok(data, L"\n", &buffer);
        data = wcstok(data, L":", &buffer);
        data = wcstok(NULL, L":", &buffer);
        sprintf(hex, "%04x", data[0]);
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