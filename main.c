#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#include<wctype.h>
#include"utils/number.h"
#include"sorting/type.h"
#include"sorting/bubble_sort.h"
#include"sorting/insertion_sort.h"
#include"sorting/selection_sort.h"
#include"sorting/merge_sort.h"
#include"sorting/heap_sort.h"
#include"sorting/quick_sort.h"

#define BUFFER_SIZE 3000
#define __wcscasecmp wcscasecmp
#define TOLOWER(Ch) towlower (Ch)

wchar_t* wcscat_m(wchar_t*, wchar_t*);


int main(int argc, char *argv[]) {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    FILE* inFile;
    FILE* outFile;
    if(argc > 1)
        inFile = fopen(argv[argc - 1], "r");
    else
        inFile = stdin;
    
    if(!inFile) {
        printf("No such file or could not open it.\n");
        exit(1);
    }

    outFile = fopen(strcat(argv[argc - 1], ".out"), "w");
    
    int counter = 0;
    int reverse = 0;
    int numerical = 0;
    int case_insensitive = 0;
    char* algorithm = "bubble_sort";
    char hex[5];
    ROW* rows;
    
    wchar_t delimeter[] = L"\n";
    wchar_t* keyPat = L"@title";
    wchar_t* begin = L"@url";
    wchar_t* end = L"@\n";
    wchar_t line[BUFFER_SIZE];
    wchar_t *buffer, *buffer2, *data;
    wchar_t argument[50];

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
            keyPat = malloc(sizeof(wchar_t) * 12);
            wcscpy(keyPat, L"@viewCount");
        } else if(strcmp(argv[i], "-c") == 0) {
            case_insensitive = 1;
        } else if(strcmp(argv[i], "-a") == 0) {
            i++;
            algorithm = malloc(sizeof(char) * (strlen(argv[i] + 1)));
            strcpy(algorithm, argv[i]);
        }
    }

    if(strcmp(algorithm, "external_merge_sort") == 0) {
        int partition_size = 3000000, more_input = 1, next = 0;
        FILE* outFile = fopen(strcat(argv[argc - 1], ".out"), "w");
        char fileName[7];
        int counter=0;
        rows = malloc(partition_size * sizeof(ROW));
        while(more_input) {
            int i;
            for(i=0; i<partition_size; i++) {
                int end_of_file = 1;
                while(fgetws(line, BUFFER_SIZE, inFile) != NULL) {
                    end_of_file = 0;
                    if(wcsstr(line, end)) {
                        *(wcsstr(line, end) + wcslen(end)) = L'\0';
                        buffer = wcscat_m(buffer, wcsstr(line, end));
                        if(wcsstr(buffer, begin)) wcscpy(buffer, wcsstr(buffer, begin));
                        if(wcsstr(buffer, keyPat) != NULL) {
                            rows[i].data = malloc(sizeof(wchar_t) * ((int)wcslen(buffer) + 1));
                            wcscpy(rows[i].data, buffer);

                            if(numerical) {
                                // rows[i].key = wcstol(data, &buffer, 10);
                            } else {
                                if(case_insensitive) sprintf(hex, "%04x", TOLOWER(wcsstr(buffer, keyPat)[wcslen(keyPat) + 1]));
                                else sprintf(hex, "%04x", wcsstr(buffer, keyPat)[wcslen(keyPat) + 1]);
                                rows[i].key = hex2dec(hex);
                            }
                        } else {
                            rows[i].key = -1;
                        }

                        wcscpy(buffer, L"");
                        break;
                    } else {
                        buffer = wcscat_m(buffer, line);
                    }
                }

                if(end_of_file == 1) {
                    more_input = 0;
                    break;
                }
            }

            merge_sort(rows, 0, i - 1, reverse);

            FILE* tmp = fopen(fileName, "w");
            for(int j=0; j<i; j++) {
                sprintf(fileName, "%d.tmp", counter);
                if(rows[j].key != -1) fprintf(tmp, "%ls", rows[j].data);
                free(rows[j].data);
                rows[j].data = malloc(sizeof(ROW) * 2);
                wcscpy(rows[j].data, L"");
            }

            fclose(tmp);
            counter++;
        }


    } else {
        rows = malloc(sizeof(ROW) * 100000);
        while(fgetws(line, BUFFER_SIZE, inFile) != NULL) {
            if(wcsstr(line, end)) {
                *(wcsstr(line, end) + wcslen(end)) = L'\0';
                buffer = wcscat_m(buffer, wcsstr(line, end));
                if(wcsstr(buffer, begin)) wcscpy(buffer, wcsstr(buffer, begin));
                if(wcsstr(buffer, keyPat) != NULL) {
                    rows[counter].data = malloc(sizeof(wchar_t) * ((int)wcslen(buffer) + 1));
                    wcscpy(rows[counter].data, buffer);
                    counter++;
                }
                
                wcscpy(buffer, L"");
            } else {
                buffer = wcscat_m(buffer, line);
            }
        }

        for(int i=0; i < counter; i++) {
            wchar_t* data = malloc(sizeof(wchar_t) * ((int)wcslen(rows[i].data) + 1));
            wcscpy(data, rows[i].data);
            data = wcsstr(data, keyPat);
            data = wcstok(data, L"\n", &buffer);
            data = wcstok(data, L":", &buffer);
            data = wcstok(NULL, L":", &buffer);
            if(data == NULL) {
                data = malloc(sizeof(wchar_t) * 2);
                wcscpy(data, L" ");
            }

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