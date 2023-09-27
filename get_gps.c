// Subroutine for get data receive
#include<string.h>
#include "ExtractValue.c"

// prototyping

/// @brief 緯度を取得する関数
/// @param GPSデータ（NMEAフォーマット）
/// @return 緯度[°]
float get_latitude(unsigned char*);

/// @brief 経度を取得する関数
/// @param GPSデータ（NMEAフォーマット）
/// @return 経度[°]
float get_longitude(unsigned char*);

/// @brief 標高を取得する関数
/// @param GPSデータ（NMEAフォーマット）
/// @return 標高[m]
float get_altitude(unsigned char*);

// get longitude from GGA message
double get_longitude(unsigned char *GPS_Data)
{
   // GGAメッセージ以外取得しないようにする
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL){ 
      return NULL;
   }

   // 区切りを「,」でしているため
   // 4個目(経度のデータが格納されている)の区切り文字を検索する
   char* FindValue = find(GGA_Message, ',', 2);

   // 次の区切りまで文字数を数える
   int LenValue = lencount(FindValue, ',');

   // 標高の値をchar -> doubleに変換してValueに格納する
   double Value = getvalue(FindValue, LenValue);

   return Value;
}

// get latirude from GGA message
float get_latitude(unsigned char *GPS_Data)
{
   // GGAメッセージ以外取得しないようにする
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL){ 
      return NULL;
   }

   // 区切りを「,」でしているため
   // 4個目(経度のデータが格納されている)の区切り文字を検索する
   char* FindValue = find(GGA_Message, ',', 4);

   // 次の区切りまで文字数を数える
   int LenValue = lencount(FindValue, ',');

   // 標高の値をchar -> doubleに変換してValueに格納する
   double Value = getvalue(FindValue, LenValue);

   return Value;
}

// get altitude value
float get_altitude(unsigned char *GPS_Data)
{
   // GGAメッセージ以外取得しないようにする
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL){ 
      return NULL;
   }

   // 区切りを「,」でしているため
   // 11個目(標高のデータが格納されている)の区切り文字を検索する
   char* FindValue = find(GGA_Message, ',', 11);

   // 次の区切りまで文字数を数える
   int LenValue = lencount(FindValue, ',');

   // 標高の値をchar -> doubleに変換してValueに格納する
   double Value = getvalue(FindValue, LenValue);

   return Value;
}