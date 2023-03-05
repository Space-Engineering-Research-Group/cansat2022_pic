//Subroutine for GPS data receive

//prototyping
float gps_lat(unsigned char*);
float gps_lon(unsigned char*);
float gps_hgt(unsigned char*);

// subroutine (get latitude data)

float gps_lat(unsigned char *x)
{
   int n1=0, n2=0, n3=0, n4=0;
   int nt1=0, nt2=0, nt3=0, nt4=0;
   float lat;
   
   n1 = (int)x[24];//before 2021.01.25 => 23,24,25,26
   n2 = (int)x[25];
   n3 = (int)x[26];
   n4 = (int)x[27];

   switch(n1){
   case 0x30: nt1 = 0;
      break;
   case 0x31: nt1 = 1;
      break;
   case 0x32: nt1 = 2;
      break;
   case 0x33: nt1 = 3;
      break;
   case 0x34: nt1 = 4;
      break;
   case 0x35: nt1 = 5;
      break;
   case 0x36: nt1 = 6;
      break;
   case 0x37: nt1 = 7;
      break;
   case 0x38: nt1 = 8;
      break;
   case 0x39: nt1 = 9;
      break;
   default: 
      break;
            }
            
   switch(n2){
   case 0x30: nt2 = 0;
      break;
   case 0x31: nt2 = 1;
      break;
   case 0x32: nt2 = 2;
      break;
   case 0x33: nt2 = 3;
      break;
   case 0x34: nt2 = 4;
      break;
   case 0x35: nt2 = 5;
      break;
   case 0x36: nt2 = 6;
      break;
   case 0x37: nt2 = 7;
      break;
   case 0x38: nt2 = 8;
      break;
   case 0x39: nt2 = 9;
      break;
   default: 
      break;
            }
            
   switch(n3){
   case 0x30: nt3 = 0;
      break;
   case 0x31: nt3 = 1;
      break;
   case 0x32: nt3 = 2;
      break;
   case 0x33: nt3 = 3;
      break;
   case 0x34: nt3 = 4;
      break;
   case 0x35: nt3 = 5;
      break;
   case 0x36: nt3 = 6;
      break;
   case 0x37: nt3 = 7;
      break;
   case 0x38: nt3 = 8;
      break;
   case 0x39: nt3= 9;
      break;
   default: 
      break;
            }

   switch(n4){
   case 0x30: nt4 = 0;
      break;
   case 0x31: nt4 = 1;
      break;
   case 0x32: nt4 = 2;
      break;
   case 0x33: nt4 = 3;
      break;
   case 0x34: nt4 = 4;
      break;
   case 0x35: nt4 = 5;
      break;
   case 0x36: nt4 = 6;
      break;
   case 0x37: nt4 = 7;
      break;
   case 0x38: nt4 = 8;
      break;
   case 0x39: nt4= 9;
      break;
   default: 
      break;
            }

   lat = 1000 * (float)nt1 + 100 * (float)nt2 + 10 * (float)nt3 + (float)nt4;
   //fprintf(xbee,"lat(gps_data) = %f\r\n",lat);
   return(lat);

}


// subroutine (get longuitude data)

float gps_lon(unsigned char *x)
{
   int e1=0, e2=0, e3=0, e4=0;
   int et1=0, et2=0, et3=0, et4=0;
   float lon;
   
   e1 = (int)x[37];//before 2021.01.25 => 36,37,38,39
   e2 = (int)x[38];
   e3 = (int)x[39];   
   e4 = (int)x[40];

   switch(e1){
   case 0x30: et1 = 0;
      break;
   case 0x31: et1 = 1;
      break;
   case 0x32: et1 = 2;
      break;
   case 0x33: et1 = 3;
      break;
   case 0x34: et1 = 4;
      break;
   case 0x35: et1 = 5;
      break;
   case 0x36: et1 = 6;
      break;
   case 0x37: et1 = 7;
      break;
   case 0x38: et1 = 8;
      break;
   case 0x39: et1 = 9;
      break;
   default: 
      break;
            }
            
   switch(e2){
   case 0x30: et2 = 0;
      break;
   case 0x31: et2 = 1;
      break;
   case 0x32: et2 = 2;
      break;
   case 0x33: et2 = 3;
      break;
   case 0x34: et2 = 4;
      break;
   case 0x35: et2 = 5;
      break;
   case 0x36: et2 = 6;
      break;
   case 0x37: et2 = 7;
      break;
   case 0x38: et2 = 8;
      break;
   case 0x39: et2 = 9;
      break;
   default: 
      break;
            }
            
   switch(e3){
   case 0x30: et3 = 0;
      break;
   case 0x31: et3 = 1;
      break;
   case 0x32: et3 = 2;
      break;
   case 0x33: et3 = 3;
      break;
   case 0x34: et3 = 4;
      break;
   case 0x35: et3 = 5;
      break;
   case 0x36: et3 = 6;
      break;
   case 0x37: et3 = 7;
      break;
   case 0x38: et3 = 8;
      break;
   case 0x39: et3= 9;
      break;
   default: 
      break;
            }

   switch(e4){
   case 0x30: et4 = 0;
      break;
   case 0x31: et4 = 1;
      break;
   case 0x32: et4 = 2;
      break;
   case 0x33: et4 = 3;
      break;
   case 0x34: et4 = 4;
      break;
   case 0x35: et4 = 5;
      break;
   case 0x36: et4 = 6;
      break;
   case 0x37: et4 = 7;
      break;
   case 0x38: et4 = 8;
      break;
   case 0x39: et4= 9;
      break;
   default: 
      break;
            }

   lon = 1000 * (float)et1 + 100 * (float)et2 + 10 * (float)et3 + (float)et4;  
   return(lon);

}

// subroutine (get height data)

float gps_hgt(unsigned char *x)
{
   int h1=0, h2=0;
   int ht1=0, ht2=0;
   int flug; 
   float hgt;

   if(x[22] != '0')
   {
         if(x[55] == ',')
         {
            //altitude : 0 - 9.0 m
            h1 = (int)x[52];
            h2 = 0;
            flug = 1;
         }
         
         else
         {
            //altitude : 10.0 - 99.0 m
            h1 = (int)x[52];
            h2 = (int)x[53];
            flug = 0;
         }
   }
   
   switch(h1){
   case 0x30: ht1 = 0;
      break;
   case 0x31: ht1 = 1;
      break;
   case 0x32: ht1 = 2;
      break;
   case 0x33: ht1 = 3;
      break;
   case 0x34: ht1 = 4;
      break;
   case 0x35: ht1 = 5;
      break;
   case 0x36: ht1 = 6;
      break;
   case 0x37: ht1 = 7;
      break;
   case 0x38: ht1 = 8;
      break;
   case 0x39: ht1 = 9;
      break;
   default: 
      break;
            }
            
   switch(h2){
   case 0x30: ht2 = 0;
      break;
   case 0x31: ht2 = 1;
      break;
   case 0x32: ht2 = 2;
      break;
   case 0x33: ht2 = 3;
      break;
   case 0x34: ht2 = 4;
      break;
   case 0x35: ht2 = 5;
      break;
   case 0x36: ht2 = 6;
      break;
   case 0x37: ht2 = 7;
      break;
   case 0x38: ht2 = 8;
      break;
   case 0x39: ht2 = 9;
      break;
   default: 
      break;
            }
            
   if(flug == 1)
      {
        hgt = (float)ht1; 
      }
   else
      {
        hgt = 10.0 * (float)ht1 + (float)ht2;
      }
      
   return(hgt);                     
   }
   
            
            
            
