#ifndef _EXTRACT_VALUE_H_
#define _EXTRACT_VALUE_H_

#include <stdlib.h>
#include <string.h>

// prototype declaration

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

#endif