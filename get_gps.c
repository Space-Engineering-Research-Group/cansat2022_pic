#include <get_gps.h>

// GPS通信のセットアップ
#use rs232(Baud = 9600, XMIT = PIN_C6, RCV = PIN_C7, stream = gps, ERRORS)

// global value
char buffer[100] = "";

char* get_GPS_Data(void)
{
   long timeout_count = 0;
   while (!kbhit())
   {
      gets(buffer);
      delay_us(10);
      timeout_count++
      if(timeout_count > 5000000)
      {
         return NULL;
      }
   }   
   return buffer;
}

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
   if(LenValue == 0){ 
      return NULL;
   }

   // 標高の値をchar -> doubleに変換してValueに格納する
   double Value = getvalue(FindValue, LenValue);

   return Value;
}

// get latirude from GGA message
float get_latitude(unsigned char *GPS_Data)
{
   // GGAメッセージ以外取得しないようにする
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL)
   { 
      return NULL;
   }

   // 区切りを「,」でしているため
   // 4個目(経度のデータが格納されている)の区切り文字を検索する
   char* FindValue = find(GGA_Message, ',', 4);

   // 次の区切りまで文字数を数える
   int LenValue = lencount(FindValue, ',');
   if(LenValue == 0)
   { 
      return NULL;
   }

   // 標高の値をchar -> doubleに変換してValueに格納する
   double Value = getvalue(FindValue, LenValue);

   return Value;
}

// get altitude value
float get_altitude(unsigned char *GPS_Data)
{
   // GGAメッセージ以外取得しないようにする
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL)
   { 
      return NULL;
   }

   // 区切りを「,」でしているため
   // 11個目(標高のデータが格納されている)の区切り文字を検索する
   char* FindValue = find(GGA_Message, ',', 11);

   // 次の区切りまで文字数を数える
   int LenValue = lencount(FindValue, ',');
   if(LenValue == 0)
   { 
      return NULL;
   }

   // 標高の値をchar -> doubleに変換してValueに格納する
   double Value = getvalue(FindValue, LenValue);

   return Value;
}

double get_angle(unsigned char* GPS_data)
{
   char *GGA_Message = strstr(GPS_data, "$GPVTG");
   if(GGA_Message == NULL)
   {
      return NULL;
   }

   char* FindValue = find(GGA_Message, ',', 1);

   int LenValue = lencount(FindValue, ',');
   if(LenValue == 0)
   {
      return NULL;
   }
}