// Subroutine for get data receive
#include<string.h>
#include "ExtractValue.c"

// prototyping
float get_latitude(unsigned char*);
float get_longitude(unsigned char*);
float get_height(unsigned char*);

// get longitude from GGA message

double get_longitude(unsigned char *GPS_Data)
{
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL){ 
      return NULL;
   }

   char* FindValue = find(GGA_Message, ',', 2);
   int LenValue = lencount(FindValue, ',');
   double Value = getvalue(FindValue, LenValue);

   return Value;
}

// get latirude from GGA message

float get_latitude(unsigned char *GPS_Data)
{
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL){ 
      return NULL;
   }

   char* FindValue = find(GGA_Message, ',', 4);
   int LenValue = lencount(FindValue, ',');
   double Value = getvalue(FindValue, LenValue);

   return Value;
}

// subroutine (get height data)

float get_height(unsigned char *GPS_Data)
{
   char *GGA_Message = strstr(GPS_Data, "$GPGGA");
   if(GGA_Message == NULL){ 
      return NULL;
   }

   char* FindValue = find(GGA_Message, ',', 11);
   int LenValue = lencount(FindValue, ',');
   double Value = getvalue(FindValue, LenValue);

   return Value;
}