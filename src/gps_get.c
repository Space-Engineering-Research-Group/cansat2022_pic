#include <stdbool.h>
//Subroutine for GPS data receive

//prototyping
float get_latitude(unsigned char*);
float get_longitude(unsigned char*);
float get_height(unsigned char*);

// subroutine (get latitude data)

float get_latitude(unsigned char *buffer){
   int north_t[4];
   float lat;
   
   int north[4] = {
      (int)buffer[24],
      (int)buffer[25],
      (int)buffer[26],
      (int)buffer[27]
   };


   for(int i = 0; i < 4; i++){
      switch(north[i]){
      case 0x30: north_t[i] = 0;
         break;
      case 0x31: north_t[i] = 1;
         break;
      case 0x32: north_t[i] = 2;
         break;
      case 0x33: north_t[i] = 3;
         break;
      case 0x34: north_t[i] = 4;
         break;
      case 0x35: north_t[i] = 5;
         break;
      case 0x36: north_t[i] = 6;
         break;
      case 0x37: north_t[i] = 7;
         break;
      case 0x38: north_t[i] = 8;
         break;
      case 0x39: north_t[i] = 9;
         break;
      default: 
         break;
      }
   }
            

   lat = 1000 * (float)north_t[0] + 100 * (float)north_t[1] + 10 * (float)north_t[2] + (float)north_t[3];
   //fprintf(xbee,"lat(gps_data) = %f\r\n",lat);
   return lat;
}


// subroutine (get longuitude data)

float get_longitude(unsigned char *buffer){
   int east_t[4];
   float lon;

   int east[4] = {
      (int)buffer[37],
      (int)buffer[38],
      (int)buffer[39],
      (int)buffer[40]
   };

   for(int i = 0; i < 4; i++){
      switch(east[i]){
      case 0x30: east_t[i] = 0;
         break;
      case 0x31: east_t[i] = 1;
         break;
      case 0x32: east_t[i] = 2;
         break;
      case 0x33: east_t[i] = 3;
         break;
      case 0x34: east_t[i] = 4;
         break;
      case 0x35: east_t[i] = 5;
         break;
      case 0x36: east_t[i] = 6;
         break;
      case 0x37: east_t[i] = 7;
         break;
      case 0x38: east_t[i] = 8;
         break;
      case 0x39: east_t[i] = 9;
         break;
      default: 
         break;
      }
   }

   lon = 1000 * (float)east_t[0] + 100 * (float)east_t[1] + 10 * (float)east_t[2] + (float)east_t[3];  
   return lon;
}

// subroutine (get height data)

float get_height(unsigned char *buffer){
   int height[2];
   int height_t[2];
   int hgt;
   bool flug = false; 

   if(buffer[22] != '0'){
         if(buffer[55] == ','){
            //altitude : 0 - 9.0 m
            height_t[0] = (int)buffer[52];
            flug = 1;
         }else{
            //altitude : 10.0 - 99.0 m
            height_t[0] = (int)buffer[52];
            height_t[1] = (int)buffer[53];
         }
   }
   
   for(int i = 0; i < 2; i++){
      switch(height[i]){
      case 0x30: height_t[i] = 0;
         break;
      case 0x31: height_t[i] = 1;
         break;
      case 0x32: height_t[i] = 2;
         break;
      case 0x33: height_t[i] = 3;
         break;
      case 0x34: height_t[i] = 4;
         break;
      case 0x35: height_t[i] = 5;
         break;
      case 0x36: height_t[i] = 6;
         break;
      case 0x37: height_t[i] = 7;
         break;
      case 0x38: height_t[i] = 8;
         break;
      case 0x39: height_t[i] = 9;
         break;
      default: 
         break;
      }
   }
            
   if(flug == 1){
        hgt = (float)height_t[0]; 
   }else{
        hgt =  10.0 * (float)height_t[0] + (float)height_t[1];
   }
   return hgt;
}