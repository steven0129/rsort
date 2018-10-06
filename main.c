#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#include<wctype.h>
#include"number.h"
#include"bubble_sort.h"
#include"insertion_sort.h"
#include"selection_sort.h"
#include"merge_sort.h"
#include"heap_sort.h"
#include"quick_sort.h"
#include"type.h"
#define BUFFER_SIZE 50000
# define __wcscasecmp wcscasecmp
# define TOLOWER(Ch) towlower (Ch)

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

    if(!inFile) {
        printf("No such file or could not open it.\n");
        exit(1);
    }
    
    int counter = 0;
    int reverse = 0;
    int numerical = 0;
    int case_insensitive = 0;
    char* algorithm = "merge_sort";
    char hex[5];
    ROW rows[400000];
    wchar_t delimeter[] = L"\n";
    wchar_t* keyPat = L"@T";
    wchar_t* begin = L"@N";
    wchar_t* end = L"@GAISRec:\n";
    wchar_t line[BUFFER_SIZE];
    wchar_t* buffer;
    wchar_t argument[100];

    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "-drl") == 0) {
            i++;
            swprintf(argument, strlen(argv[i]) + 1, L"%s", argv[i]);
            end = malloc(sizeof(wchar_t) * (wcslen(argument) + 1));
            wcscpy(end, argument);
        } else if(strcmp(argv[i], "-drb") == 0) {
            i++;
            swprintf(argument, strlen(argv[i]) + 1, L"%s", argv[i]);
            begin = malloc(sizeof(wchar_t) * (wcslen(argument) + 1));
            wcscpy(begin, argument);
        } else if(strcmp(argv[i], "-k") == 0) {
            i++;
            swprintf(argument, strlen(argv[i]) + 1, L"%s", argv[i]);
            keyPat = malloc(sizeof(wchar_t) * (wcslen(argument) + 1));
            wcscpy(keyPat, argument);
        } else if(strcmp(argv[i], "-r") == 0) {
            reverse = 1;
        } else if(strcmp(argv[i], "-n") == 0) {
            numerical = 1;
            keyPat = malloc(sizeof(wchar_t) * 3);
            wcscpy(keyPat, L"@N");
        } else if(strcmp(argv[i], "-c") == 0) {
            case_insensitive = 1;
        } else if(strcmp(argv[i], "-a") == 0) {
            i++;
            algorithm = malloc(sizeof(char) * (strlen(argv[i] + 1)));
            strcpy(algorithm, argv[i]);
        }
    }

    while(fgetws(line, sizeof(line), inFile) != NULL) {
        buffer = wcscat_m(buffer, line);
        rows[counter].idx = counter;

        while(fgetws(line, sizeof(line), inFile) != NULL) {
            if(wcsstr(line, end)) {
                *(wcsstr(line, end) + wcslen(end)) = L'\0';
                buffer = wcscat_m(buffer, wcsstr(line, end));
                if(wcsstr(buffer, begin)) wcscpy(buffer, wcsstr(buffer, begin));
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

        if(numerical) {
            rows[i].key = wcstol(data, &buffer, 10);
        } else {
            if(case_insensitive) sprintf(hex, "%04x", TOLOWER(data[0]));
            else sprintf(hex, "%04x", data[0]);
            rows[i].key = hex2dec(hex);
        }
    }
    
    if(strcmp(algorithm, "bubble_sort") == 0) bubble_sort(rows, counter, reverse);
    else if(strcmp(algorithm, "insertion_sort") == 0) insertion_sort(rows, counter, reverse);
    else if(strcmp(algorithm, "selection_sort") == 0) selection_sort(rows, counter, reverse);
    else if(strcmp(algorithm, "merge_sort") == 0) merge_sort(rows, 0, counter - 1, reverse);
    else if(strcmp(algorithm, "heap_sort") == 0) heap_sort(rows, counter, reverse);
    else if(strcmp(algorithm, "quick_sort") == 0) quick_sort(rows, 0, counter - 1, reverse);

    for(int i = 0; i < counter; i++) {
        printf("%ls", rows[i].data);
    }
}

wchar_t* wcscat_m(wchar_t* str1, wchar_t* str2) {
    int len = 0;
    wchar_t* s;

    if(str1 != NULL) len = sizeof(wchar_t) * ((int)wcslen(str1) + 1);
    len += sizeof(wchar_t) * ((int)wcslen(str2) + 1);
    s = realloc(str1, len);
    wcscat(s, str2);
    return s;
}