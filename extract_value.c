#include <stdlib.h>
#include <string.h>
#include <extract_value.h>

char* find(char *text, char target, int target_num){
    size_t len = strlen(text);
    int count = 0;

    for(int i = 0; i < len; i++){
        if(text[i] == target){
            count++;
            if(count == target_num){
                return text + i;
            }
        }
    }

    return NULL;
}

int lencount(char* text, char target){
    size_t len = strlen(text);
    text += 1;

    if(*text == ','){ 
        return 0;
    }
    for(int i = 1; i < len; i++){
        if(*(text + i) == target){
            return i;          
        }
    }
}

double getvalue(char* text, int len){
    double value;
    char* char_value;

    text += 1;
    for(int i = 0; i < len; i++){
        char_value[i] = text[i];
    }

    value = atof(char_value);  
    return value;
}
