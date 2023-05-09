//Subroutine for GPS data receive

//prototyping
float get_latitude(unsigned char*);
float get_longitude(unsigned char*);
float get_height(unsigned char*);

// subroutine (get latitude data)

float get_latitude(unsigned char *buffer)
{
   int nt[4];
   float lat;
   
   int n[] = {
      (int)buffer[24],
      (int)buffer[25],
      (int)buffer[26],
      (int)buffer[27]
   };


   for(int i = 0; i < 4; i++){
      switch(n[i]){
      case 0x30: nt[i] = 0;
         break;
      case 0x31: nt[i] = 1;
         break;
      case 0x32: nt[i] = 2;
         break;
      case 0x33: nt[i] = 3;
         break;
      case 0x34: nt[i] = 4;
         break;
      case 0x35: nt[i] = 5;
         break;
      case 0x36: nt[i] = 6;
         break;
      case 0x37: nt[i] = 7;
         break;
      case 0x38: nt[i] = 8;
         break;
      case 0x39: nt[i] = 9;
         break;
      default: 
         break;
               }
   }
            

   lat = 1000 * (float)nt[0] + 100 * (float)nt[1] + 10 * (float)nt[2] + (float)nt[3];
   //fprintf(xbee,"lat(gps_data) = %f\r\n",lat);
   return(lat);

}


// subroutine (get longuitude data)

float get_longitude(unsigned char *buffer)
{
   int et[4];
   float lon;

   int e[] = {
      (int)buffer[37],
      (int)buffer[38],
      (int)buffer[39],
      (int)buffer[40]
   };

   for(int i = 0; i < 4; i++){
      switch(e[i]){
      case 0x30: et[i] = 0;
         break;
      case 0x31: et[i] = 1;
         break;
      case 0x32: et[i] = 2;
         break;
      case 0x33: et[i] = 3;
         break;
      case 0x34: et[i] = 4;
         break;
      case 0x35: et[i] = 5;
         break;
      case 0x36: et[i] = 6;
         break;
      case 0x37: et[i] = 7;
         break;
      case 0x38: et[i] = 8;
         break;
      case 0x39: et[i] = 9;
         break;
      default: 
         break;
               }
   }

   lon = 1000 * (float)et[0] + 100 * (float)et[1] + 10 * (float)et[2] + (float)et[3];  
   return(lon);

}

// subroutine (get height data)

float get_height(unsigned char *buffer){
   int h[] = {0, 0};
   int ht[] = {0, 0};
   int flug; 
   float hgt;

   if(buffer[22] != '0'){
         if(buffer[55] == ','){
            //altitude : 0 - 9.0 m
            h = {
               (int)buffer[52],
               0
            };
            flug = 1;
         }else{
            //altitude : 10.0 - 99.0 m
            h = {
               (int)buffer[52],
               (int)buffer[53]
            };
            flug = 0;
         }
   }
   
   for(int i = 0; i < 2; i++){
      switch(h[i]){
      case 0x30: ht[i] = 0;
         break;
      case 0x31: ht[i] = 1;
         break;
      case 0x32: ht[i] = 2;
         break;
      case 0x33: ht[i] = 3;
         break;
      case 0x34: ht[i] = 4;
         break;
      case 0x35: ht[i] = 5;
         break;
      case 0x36: ht[i] = 6;
         break;
      case 0x37: ht[i] = 7;
         break;
      case 0x38: ht[i] = 8;
         break;
      case 0x39: ht[i] = 9;
         break;
      default: 
         break;
               }
   }
            
   if(flug == 1)
      {
        hgt = (float)ht[0]; 
      }
   else
      {
        hgt = 10.0 * (float)ht[0] + (float)ht[1];
      }
      
   return(hgt);                     
   }