#include<stdlib.h>
#include <string.h>

// プロトタイプ宣言

/// @brief targetで検索文字を指定すると検索させた文字列のアドレスが返ってきます
/// @param text 検索させたい文字列の先頭アドレス
/// @param target 検索させる文字
/// @param target_num 複数の文字がある場合のいくつ目の文字を指定
/// @return 検索した文字のアドレス
char* find(char* text, char target, int target_num);

/// @brief 検索する文字列までカウントします
/// @param text 検索させたい文字列の先頭アドレス
/// @param target 検索したい文字
/// @return カウントした数字
int lencount(char* text, char target);

/// @brief 抽出したい文字列を数値に変換する関数です
/// @param text 抽出させる文字列の先頭アドレス
/// @param len 抽出したい文字列の長さ
/// @return 抽出した数値
double getvalue(char* text, int len);
 
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

    for(int i = 1; i < len; i++){
        if(*(text + i) == target){
            return i;          
        }
    }

    return 0;
}

double getvalue(char* text, int len){
    double value;
    char char_value[len];

    text += 1;
    for(int i = 0; i < len; i++){
        char_value[i] = *(text + i);
    }

    value = atof(char_value);  
    return value;
}