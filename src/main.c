// #include <18f2550.h> //pic library
// #include <18f2455.h>

// #fuses HS,NOWDT,NOPROTECT,PUT,BROWNOUT,NOLVP
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <i2c_LCD_lib.c>

// #use fast_io(A)
// #use fast_io(B)
// #use fast_io(C)


// RS232C setup
// #use delay(CLOCK=20000000)
// #use rs232(Baud = 9600, XMIT = PIN_C6, RCV = PIN_C7, stream = gps, ERRORS)
// #use rs232(Baud = 9600, XMIT = PIN_B2, RCV = PIN_B3, stream = xbee)
// #use i2c(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
// #byte UCFG = 0xF6F
// #bit UTRDIS = UCFG.3

//global variables
unsigned char buffer[100];
float n_posi,e_posi;  //present position
float dest[2],zero[2],vec_a[2],dest_a[2],origin[2];
float des_n_posi=4566.0, des_e_posi=6068.0;  //destination Tanegashima Goals
float abs_dest_a, abs_vec_a, in_prod, crs_prod,bef_abs_dest_a;
float pai;
double angle;
int fall; // Bright : fall = 0, Dark: fall = 1
int i=0,f=0,j,h,survo,setmode,k = 10;
long int pin_wait = 5; //wait time after para is opened
long int gps_count,left_angle,right_angle;
float height;
int32_t s_time, s, x;
double left_time = 1700.0;        //    left turn time setting [ms]
double right_time= 1700.0;       //    right turn time setting [ms]

//other function definition
#include "motor.c"
#include "gps_get.c"
#include "gps_cal.c"
                                    
typedef struct {
   float latitude;
   float longitude;
} Goals;

typedef struct {
   float latitude;
   float longitude;
   float height;
} Earth_Coordinates;

typedef struct {
   double left;
   double right;
} Motor_Time;

typedef struct {
   long int left;
   long int right;
} Gps_Angles;

void main(){

   // start

   long int pin_wait = 5; //wait time after para is opened
   float pi = acos(-1.0);
   int fall = input(PIN_B4);
   int setmode;
   double angle;
   unsigned char buffer[100], text[2][50];
   Goals goal;
   Earth_Coordinates earth_cd;
   Motor_Time motor_time;
   Gps_Angles gps_angle;

   // USB disable
   UTRDIS = 1;

   //setting

   set_tris_A(0x00); //All of A ports are output mode
   set_tris_B(0x18); //B3 and B4 pin are inputs, other B ports are output mode
   set_tris_C(0x80); //C7 pin is input mode. C4 and C5 are "always input mode" when USB is disabled. Other C ports are output mode.

   stop();
   
   // i2c LCD initialize
   lcd_init();
   
   sprintf(text[0],"Power ON");
   lcd_clear();
   lcd_str(text[0]);
   delay_ms(1000);
   
   //  delay_ms(1000);

   // setting the Goal coordinatenacho_dayo

   goal.longitude = 4566.0;
   goal.latitude = 6068.0;
   sprintf(text[0],"GoalLongitude = %f",goal.longitude);
   sprintf(text[1],"GoalLatitude = %f",goal.latitude);
   lcd_clear();
   lcd_str(text[0]);
   lcd_cmd(0xC0);
   lcd_str(text[1]);
   
   fprintf(xbee,"Power ON\r\n");
   output_low(PIN_B5); //output for servo

   // wait for accurate data

   // fprintf(xbee,"Experiment Ready 1\r\n");
   gets(buffer);
   //fprintf(xbee,"buffer=%s\r\n",buffer);
   fprintf(xbee,"Experiment Ready \r\n");
   gets(buffer);
   //fprintf(xbee,"buffer=%s\r\n",buffer);

   do{         
      gets(buffer);
      earth_cd.latitude = get_latitude(buffer);
      earth_cd.longitude = get_longitude(buffer);
      fprintf(xbee,"GPS is setting\r\n");
      //fprintf(xbee,"buffer=%s\r\n",buffer);
   }while(buffer[22] == ',');

   long int gps_count = 0;
   
   do{
      //fprintf(xbee,"set-mode %d\r\n",setmode);
      //fprintf(xbee,"set-mode-1 %ld\r\n",gps_count);
      fprintf(xbee,"fall = %d\r\n",fall);
      gets(buffer);
      //fprintf(xbee,"buffer=%S\r\n",buffer);
      //delay_ms(2990);
      gps_count++;
   }while(gps_count < 20 && fall == 0);

   //operation mode
   fprintf(xbee,"Op-mode %d\r\n",setmode);
   gets(buffer);
   //fprintf(xbee,"buffer=%S\r\n",buffer);

   //wait for launch and landing
   do{
      gets(buffer);
      //fprintf(xbee,"buffer=%s\r\n",buffer);
      earth_cd.latitude = get_latitude(buffer);
      earth_cd.longitude = get_longitude(buffer);
      earth_cd.height = get_height(buffer);
      gps_count++;

      //delay_ms(500);
      fprintf(xbee,"%ld : Altitude:%.0f\r\n",gps_count,height);
      sprintf(text[0],"%ld : Altitude:%.0f",gps_count,height);
      lcd_clear();
      lcd_str(text[0]);
      //delay_ms(500);
      
   }while(fall == 1 && gps_count < 300);
   
   fprintf(xbee,"Parachute is opened\r\n");
   sprintf(text[0],"Parachute is opened");
   lcd_clear();
   lcd_str(text[0]);
   
   //pin wait
   for(int i = 0; i <= pin_wait; i++){
      gets(buffer);
      gps_count++;
      fprintf(xbee,"%ld : Altitude:%.0f,CountDown:%ld\r\n",gps_count, height, pin_wait - i);
      sprintf(text[0],"%ld : Altitude:%.0f",gps_count, height);
      sprintf(text[1],"Count:%ld",pin_wait - i);
      lcd_clear();
      lcd_str(text[0]);
      lcd_cmd(0xC0);
      lcd_str(text[1]);
      
      if(i == (pin_wait - 1)){
       fprintf(xbee,"Servo On\r\n"); 
         //Servo On  duty 7.4% = 90deg (open)
         for(int survo=0; survo < 25; survo++){
            output_high(PIN_B5);
            delay_us(1480);
            output_low(PIN_B5);
            delay_us(18520);
         }
         gets(buffer);
         //duty 12% =  180deg
         for(survo = 0; survo < 25; survo++){
            output_high(PIN_B5);
            delay_us(2400);
            output_low(PIN_B5);
            delay_us(17600);
         }
         // endif
      }
      // endfor
    }   


   // Navigation start   
   fprintf(xbee,"Navigation Start \r\n");
   sprintf(text[0],"Navigation Start");
   sprintf(text[1],"Target:%4.0f,%4.0f",goal.longitude, goal.latitude);
   lcd_clear();
   lcd_str(text[0]);
   lcd_cmd(0xC0);
   lcd_str(text[1]);
   fprintf(xbee,"Target:%4.0f,%4.0f \r\n",goal.longitude, goal.latitude);
   forward();
   gps_count = 1;

   // Keep distance from parachute
   for(i = 0; i < 12; i++){
      gets(buffer);
      fprintf(xbee,"forward %ld \r\n",gps_count);
      gps_count++;
   }
   
   // end fall part

   float starting_point[2] = {
      earth_cd.latitude,
      earth_cd.longitude
   };
   
   // start to go to Goal
   //loop----------------------------------------------   
   while(1){ 
      //fprintf(xbee,"k=%d\r\n",k);
      gps_get();
      calculate();
      turn_check();
      back_check();
      
      int direction = 10;
      if(direction > 15){
         left_turn();
         for(i = 0; i < 6; i++){
            delay_ms(250);
         }
         direction = 10;
         fprintf(xbee,"turn left\r\n");
      }
      if(direction < 5){
         stop();
         gets(buffer);
         right_turn(); // turn right
         for(i = 0; i < 3; i++){
            delay_ms(250);
         }
         stop();
         gets(buffer);
         right_turn(); // turn right
         for(i = 0; i < 3; i++){
            delay_ms(250);
         }
         direction = 10;
         fprintf(xbee,"turn right\r\n");
      }
      
      // print to log file
      fprintf(xbee,"%ld : %4.0f,%4.0f,DIST: %.0f,L:%ld,R:%ld,direction = %d \r\n",gps_count, earth_cd.longitude, earth_cd.latitude,abs_dest_a, gps_angle.left, gps_angle.right, direction);
      //fprintf(xbee,"buffer=%s\r\n",buffer);// To compare GPS rawdata with components of array 
      sprintf(text[0],"%4.0f DIST:%f",earth_cd.longitude ,abs_dest_a);
      sprintf(text[1],"%4.0f L:%ld,R:%ld,direction = %d", earth_cd.latitude, gps_angle.left, gps_angle.right, direction);
      lcd_clear();
      lcd_str(text[0]);
      lcd_cmd(0xC0);
      lcd_str(text[1]);
      if(j != 0 && f == 0){ 
         forward();
      }
      j++;
      if(j == 6){j = 0;}
      
      if(abs_dest_a < 10){    // 10m以内に到着
         stop();
         fprintf(xbee,"mission complete\r\n");
         break;
       }
   }
   stop();
   // end
}
