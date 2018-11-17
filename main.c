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
#define CHUNK_SIZE 1024

long int fileLen(FILE*);

int main(int argc, char* argv[]) {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    FILE* inFile;
    FILE* outFile;
    int fileNum = 0;
    
    char* BEGIN = "@\n@url";
    char* KEY_PAT = "@content:";
    
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
        
        for(int counter = 0;; counter++) {
            char hex[9];
            int dec;
            rows[counter].data = strdup(chunk);
            
            if(strstr(rows[counter].data + strlen(BEGIN), BEGIN) == NULL) {
                counter--;
                break;
            }

            *strstr(rows[counter].data + strlen(BEGIN), BEGIN) = '\0';
            fp += strlen(rows[counter].data);
            sprintf(hex, "%08x", *(strstr(rows[counter].data, KEY_PAT) + strlen(KEY_PAT)));
            dec = hex2dec(hex);
            rows[counter].key = dec;
            rows[counter].fileNum = fileNum;
            chunk = strdup(strstr(chunk + strlen(BEGIN), BEGIN));
        }

        free(chunk);
        free(rows);
    }
    

    fclose(inFile);
    return 0;
}

long int fileLen(FILE* file) {
    fseek(file, 0, SEEK_END);
    return ftell(file);
}