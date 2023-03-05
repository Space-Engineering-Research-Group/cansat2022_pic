#include <18f2550.h>
//#include <18f2455.h>

#fuses HS,NOWDT,NOPROTECT,PUT,BROWNOUT,NOLVP
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)


// RS232C setup
#use delay(CLOCK=20000000)
#use rs232(Baud = 9600, XMIT = PIN_C6, RCV = PIN_C7, stream = gps, ERRORS)
#use rs232(Baud = 9600, XMIT = PIN_B2, RCV = PIN_B3, stream = xbee)
#use i2c(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#byte UCFG = 0xF6F
#bit UTRDIS = UCFG.3
#include <i2c_LCD_lib.c>
long int pin_wait = 5; //wait time after para is opened

//global variables
unsigned char buffer[100];
float n_posi,e_posi;  //present position
float dest[2],zero[2],vec_a[2],dest_a[2],origin[2];
float des_n_posi=4566.0, des_e_posi=6068.0;  //destination Tanegashima goals
float abs_dest_a, abs_vec_a, in_prod, crs_prod,bef_abs_dest_a;
float pai;
double angle;
int fall; // Bright : fall = 0, Dark: fall = 1
int i=0,f=0,j,h,survo,setmode,k = 10;
long int gps_rcv,left_angle,right_angle;
float height;
int32 s_time, s, x;
double left_time = 1700.0;        //    left turn time setting [ms]
double right_time= 1700.0;       //    right turn time setting [ms]
unsigned char text1[50],text2[50];

//other function definition
#include "spin.c"
#include "gps_data.c"
#include "gps_cal.c"
                                    


void main(){

// USB disable
UTRDIS = 1;

//setting

   set_tris_A(0x00); //All of A ports are output mode
   set_tris_B(0x18); //B3 and B4 pin are inputs, other B ports are output mode
   set_tris_C(0x80); //C7 pin is input mode. C4 and C5 are "always input mode" when USB is disabled. Other C ports are output mode.

   stop();
   
   // i2c LCD initialize
   lcd_init();
   
   sprintf(text1,"Power ON");
   lcd_clear();
   lcd_str(text1);
   delay_ms(1000);
   
 //  delay_ms(1000);
   sprintf(text1,"n_posi=%f",des_n_posi);
   sprintf(text2,"e_posi=%f",des_e_posi);
   lcd_clear();
   lcd_str(text1);
   lcd_cmd(0xC0);
   lcd_str(text2);
   
   fprintf(xbee,"Power ON\r\n");
   pai = acos(-1.0);   
   output_low(PIN_B5); //output for servo
   
   
   h = 0;
   gps_rcv = 0;
   fall = 0;
   setmode = 0;

// wait for accurate data

//   fprintf(xbee,"Experiment Ready 1\r\n");
   gets(buffer);
   //fprintf(xbee,"buffer=%s\r\n",buffer);
   fprintf(xbee,"Experiment Ready \r\n");
   gets(buffer);
   //fprintf(xbee,"buffer=%s\r\n",buffer);

   do
   {         
      gets(buffer);
      n_posi = gps_lat(buffer);
      e_posi = gps_lon(buffer);
      fprintf(xbee,"GPS setting\r\n");
      //fprintf(xbee,"buffer=%s\r\n",buffer);
   }
   while(buffer[22] == ',' 
         && buffer[22] == ','
         && buffer[22] == ','
         && buffer[22] == ',');

   
do{
   //fprintf(xbee,"set-mode %d\r\n",setmode);
   //fprintf(xbee,"set-mode-1 %ld\r\n",gps_rcv);
   fprintf(xbee,"fall = %d\r\n",fall);
   gets(buffer);
   //fprintf(xbee,"buffer=%S\r\n",buffer);
   //delay_ms(2990);
   gps_rcv++;
   fall = input(PIN_B4);
}
while(gps_rcv<20&&fall == 0 );

   //operation mode
   fprintf(xbee,"Op-mode %d\r\n",setmode);
   gets(buffer);
   //fprintf(xbee,"buffer=%S\r\n",buffer);

//wait for launch and landing
   do{
      gets(buffer);
      //fprintf(xbee,"buffer=%s\r\n",buffer);
      n_posi = gps_lat(buffer);
      e_posi = gps_lon(buffer);
      height = gps_hgt(buffer);
      gps_rcv++;

      //delay_ms(500);
      fprintf(xbee,"%ld : LM:%.0f\r\n",gps_rcv,height);
      sprintf(text1,"%ld : LM:%.0f",gps_rcv,height);
      lcd_clear();
      lcd_str(text1);
      //delay_ms(500);
      
      fall = input(PIN_B4);
   }
   while((fall == 1) && (gps_rcv < 300));
   
   fprintf(xbee,"Parachute is opened\r\n");
   sprintf(text1,"Para is opened");
   lcd_clear();
   lcd_str(text1);
   
   zero[0]=e_posi;
   zero[1]=n_posi;
   origin[0]=e_posi;
   origin[1]=n_posi;

//pin wait
   for(i=0;i<=pin_wait;i++){
      gets(buffer);
      gps_rcv++;
      fprintf(xbee,"%ld : LM:%.0f,CountDown:%ld\r\n",gps_rcv,height,pin_wait-i);
      sprintf(text1,"%ld : LM:%.0f",gps_rcv,height);
      sprintf(text2,"Count:%ld",pin_wait-i);
      lcd_clear();
      lcd_str(text1);
      lcd_cmd(0xC0);
      lcd_str(text2);
      
      if(i==(pin_wait - 1))
      {
       fprintf(xbee,"Servo On\r\n");
       
//Servo On
// duty 7.4% = 90deg (open)
         for(survo=0;survo<25;survo++){
            output_high(PIN_B5);
            delay_us(1480);
            output_low(PIN_B5);
            delay_us(18520);
         }
    gets(buffer);
         
//duty 12% =  180deg
         for(survo=0;survo<25;survo++){
            output_high(PIN_B5);
            delay_us(2400);
            output_low(PIN_B5);
            delay_us(17600);
         }

      }
    }   


// Navigation start   
   fprintf(xbee,"Navigation Start \r\n");
   sprintf(text1,"Navigation Start");
   sprintf(text2,"Target:%4.0f,%4.0f",des_n_posi,des_e_posi);
   lcd_clear();
   lcd_str(text1);
   lcd_cmd(0xC0);
   lcd_str(text2);
   fprintf(xbee,"Target:%4.0f,%4.0f \r\n",des_n_posi,des_e_posi);
   forward();
   gps_rcv=1;

// Keep distance from parachute
   for(j = 0; j < 12; j++)
   {
      gets(buffer);
      //gps_rcv++;
      fprintf(xbee,"forward %ld \r\n",gps_rcv);
      gps_rcv++;
   }
   j = 0;
   
   
//loop----------------------------------------------   
   while(1){ 
      //fprintf(xbee,"k=%d\r\n",k);
      gps_get();
      calculate();
      turn_check();
      back_check();
      
      if(k > 15)
      {
         left_turn(); // turn left
         for(x = 0; x < 6; x++)
         {
            delay_ms(250);
         }
         k = 10;
         fprintf(xbee,"left turn\r\n");
      }
      
      if(k < 5)
      {
         stop();
         gets(buffer);
         right_turn(); // turn right
         for(x = 0; x < 3; x++)
         {
            delay_ms(250);
         }
         stop();
         gets(buffer);
         right_turn(); // turn right
         for(x = 0; x < 3; x++)
         {
            delay_ms(250);
         }
         k = 10;
         fprintf(xbee,"right turn\r\n");
      }
      
      fprintf(xbee,"%ld : %4.0f,%4.0f,DIST: %.0f,L:%ld,R:%ld,k=%d \r\n",gps_rcv,n_posi,e_posi,abs_dest_a,left_angle,right_angle,k);
      //fprintf(xbee,"buffer=%s\r\n",buffer);// To compare GPS rawdata with components of array 
      sprintf(text1,"%4.0f DIST:%f",n_posi,abs_dest_a);
      sprintf(text2,"%4.0f L:%ld,R:%ld,k%d",e_posi,left_angle,right_angle,k);
      lcd_clear();
      lcd_str(text1);
      lcd_cmd(0xC0);
      lcd_str(text2);
      if((j != 0)&&(f==0))
      { 
         forward();
      }
      j++;
      if(j == 6){j = 0;}
      
      if(abs_dest_a < 10) //default = 10
       {
         stop();
         fprintf(xbee,"mission complete\r\n");
         break;
       }
      
   }

   stop();
}
