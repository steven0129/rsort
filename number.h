#ifndef NUMBER_H
#define NUMBER_H
#include<string.h>

int get_signs_index(char);
int hex2dec(char*);

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

#endif