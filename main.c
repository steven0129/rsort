#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#define BUFFER_SIZE 50000

typedef struct {
    int idx;
    int key;
    wchar_t* data;
} ROW;

wchar_t* wcscat_m(wchar_t*, wchar_t*);
wchar_t* str_replace (wchar_t *source, wchar_t *find,  wchar_t *rep);

int main(int argc, char *argv[]) {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    FILE* inFile = fopen(argv[argc - 1], "r");
    if(inFile == NULL) {
        printf("No such file or could not open it.\n");
        exit(1);
    }
    int debug = 0;
    int counter = 0;
    int loading = 0;
    ROW rows[400000];
    wchar_t delimeter[] = L"\n";
    wchar_t* keyPat = L"@T";
    wchar_t* begin = L"@GAISRec:";
    wchar_t* end = L"@GAISRec:";
    wchar_t line[BUFFER_SIZE];

    while(fgetws(line, sizeof(line), inFile) != NULL) {
        wchar_t* tmp = (wchar_t*)malloc(sizeof(wchar_t) * ((int)wcslen(line) + 1));
        wchar_t* str;
        wcscpy(tmp, line);
        rows[counter].idx = counter;

        if(!loading && wcsstr(tmp, begin)) {
            loading = 1;
            str = wcscat_m(str, wcsstr(tmp, begin));
        }

        while(loading && fgetws(line, sizeof(line), inFile) != NULL) {
            size_t newSize = sizeof(wchar_t) * ((int)wcslen(line) + 1);
            tmp = (wchar_t*)malloc(newSize);
            wcscpy(tmp, line);

            if(wcsstr(tmp, end)) {
                wchar_t* buffer;
                str = wcscat_m(str, wcstok(tmp, end, &buffer));
                loading = 0;
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
        wchar_t* result = wcsstr(rows[i].data, keyPat);
        wchar_t* buffer;
        result = wcstok(result, L"\n", &buffer);
        result = wcstok(result, L":", &buffer);
        result = wcstok(NULL, L":", &buffer);
        rows[i].key = (int)*result;
        printf("%d", rows[i].key);
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

wchar_t* str_replace(wchar_t *source, wchar_t *find,  wchar_t *rep) {  
   // 搜尋文字的長度  
   int find_L=wcslen(find);  
   // 替換文字的長度  
   int rep_L=wcslen(rep);  
   // 結果文字的長度  
   int length=wcslen(source)+1;  
   // 定位偏移量  
   int gap=0;  
     
   // 建立結果文字，並複製文字  
   wchar_t *result = (wchar_t*)malloc(sizeof(wchar_t) * length);  
   wcscpy(result, source);      
     
   // 尚未被取代的字串  
   wchar_t *former=source;  
   // 搜尋文字出現的起始位址指標  
   wchar_t *location= wcsstr(former, find);  
     
   // 漸進搜尋欲替換的文字  
   while(location!=NULL){  
       // 增加定位偏移量  
       gap+=(location - former);  
       // 將結束符號定在搜尋到的位址上  
       result[gap]='\0';  
         
       // 計算新的長度  
       length+=(rep_L-find_L);  
       // 變更記憶體空間  
       result = (wchar_t*)realloc(result, length * sizeof(wchar_t));  
       // 替換的文字串接在結果後面  
       wcscat(result, rep);  
       // 更新定位偏移量  
       gap+=rep_L;  
         
       // 更新尚未被取代的字串的位址  
       former=location+find_L;  
       // 將尚未被取代的文字串接在結果後面  
       wcscat(result, former);  
         
       // 搜尋文字出現的起始位址指標  
       location= wcsstr(former, find);  
   }      
  
   return result;  
  
}