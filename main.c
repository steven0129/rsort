#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#include<wctype.h>
#include<limits.h>
#include<string.h>
#include"sorting/type.h"
#include"sorting/quick_sort.h"
#include"utils/number.h"

#define __wcscasecmp wcscasecmp
#define TOLOWER(Ch) towlower (Ch)
long int fileLen(FILE*);

int main(int argc, char* argv[]) {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    FILE* inFile;
    FILE* outFile;
    int fileNum = 0, reverse = 0;
    char* BEGIN = "@\n@url";
    char* KEY_PAT = "@content:";
    unsigned long long int CHUNK_SIZE = 1 << 20;
    
    if(argc > 1)
        inFile = fopen(argv[argc - 1], "r");
    else
        inFile = stdin;
    
    if(!inFile) {
        printf("No such file or could not open it.\n");
        exit(1);
    }

    for(long int fp = 0; fp < fileLen(inFile); fileNum++) {
        printf("%d\n", fileNum);
        char* chunk = (char*)malloc(sizeof(char) * CHUNK_SIZE);
        ROW* rows = (ROW*)malloc(sizeof(char) * (CHUNK_SIZE + 10) + sizeof(int) * (CHUNK_SIZE + 10) * 2);
        fseek(inFile, fp, SEEK_SET);
        fread(chunk, sizeof(char), CHUNK_SIZE, inFile);
        int counter;
        for(counter = 0;; counter++) {
            char hex[9];
            int dec;
            rows[counter].data = malloc(5000 * sizeof(char));
            strncpy(rows[counter].data, chunk, 5000 * sizeof(char));
            
            if(strstr(rows[counter].data + strlen(BEGIN), BEGIN) == NULL) {
                counter--;
                quick_sort(rows, 0, counter - 1, reverse);
                break;
            }

            *strstr(rows[counter].data + strlen(BEGIN), BEGIN) = '\0';
            fp += strlen(rows[counter].data);
            sprintf(hex, "%08x", *(strstr(rows[counter].data, KEY_PAT) + strlen(KEY_PAT)));
            dec = hex2dec(hex);
            rows[counter].key = dec;
            rows[counter].fileNum = fileNum;
            strcpy(chunk, strstr(chunk + strlen(BEGIN), BEGIN));
        }

        char tmpName[30];
        sprintf(tmpName, "temp%d", fileNum);
        FILE* tmp = fopen(tmpName, "w");
        for(int i=0; i < counter; i++) {
            fwrite(rows[i].data, sizeof(char), strlen(rows[i].data), tmp);
            free(rows[i].data);
        }

        free(chunk);
        free(rows);
        fclose(tmp);
    }
    

    fclose(inFile);
    return 0;
}

long int fileLen(FILE* file) {
    fseek(file, 0, SEEK_END);
    return ftell(file);
}