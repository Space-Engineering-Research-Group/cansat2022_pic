// #include <18f2550.h> //pic library
// #include <18f2455.h>

#fuses HS,points->nowDT,NOPROTECT,PUT,BROWNOUT,NOLVP
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

//other function definition
#include "motor.c"
#include "gps_get.c"
#include "gps_cal.c"
#include "i2c_LCD_lib.c"

void main(void){

   // start
   long int pin_wait = 5; //wait time after para is opened
   float pi = acos(-1.0);
   int fall = input(PIN_B4);
   int setmode;
   unsigned char buffer[100], text[2][50];
   struct Pins pins;
   struct Points points;
   Motor_Time motor_time;
   Gps_Angles gps_angle;

   // USB disable
   UTRDIS = 1;

   //settings
   set_tris_A(0x00); // All of A ports are output mode
   set_tris_B(0x18); // B3 and B4 pin are inputs, other B ports are output mode
   set_tris_C(0x80); // C7 pin is input mode. C4 and C5 are "always input mode" when USB is disabled. Other C ports are output mode.

   // set motor pins
   pins.forword.left = PIN_C0;
   pins.back.left = PIN_C1;
   pins.forword.right = PIN_A0;
   pins.back.right = PIN_C2;

   stop(&pins);
   
   // i2c LCD initialize
   lcd_init();
   
   sprintf(text[0],"Power ON");
   lcd_clear();
   lcd_str(text[0]);
   delay_ms(1000);

   // setting the Goal coordinatenacho_dayo
   points.goal.longitude = 4566.0;
   points.goal.latitude = 6068.0;
   sprintf(text[0],"GoalLongitude = %f",points.goal.longitude);
   sprintf(text[1],"GoalLatitude = %f",points.goal.latitude);
   lcd_clear();
   lcd_str(text[0]);
   lcd_cmd(0xC0);
   lcd_str(text[1]);

   motor_time.right = 1700.0;
   motor_time.left = 1700.0;
   
   fprintf(xbee,"Power ON\r\n");
   output_low(PIN_B5); // output for servo

   // wait for accurate data
   long int gps_count = 0;

   gets(buffer);
   fprintf(xbee,"Experiment Ready \r\n");
   gets(buffer);

   do{         
      gets(buffer);
      points.now.latitude = get_latitude(buffer);
      points.now.longitude = get_longitude(buffer);
      fprintf(xbee,"GPS is setting\r\n");
   }while(buffer[22] == ',');

   do{
      fprintf(xbee,"fall = %d\r\n",fall);
      gets(buffer);
      gps_count++;
   }while(gps_count < 20 && fall == 0);

   // operation mode
   fprintf(xbee,"Op-mode %d\r\n",setmode);
   gets(buffer);

   // wait for launch and landing
   do{
      gets(buffer);
      points.now.latitude = get_latitude(buffer);
      points.now.longitude = get_longitude(buffer);
      points.now.height = get_height(buffer);
      gps_count++;

      fprintf(xbee,"%ld : Altitude:%.0f\r\n", gps_count, points.now.height);
      sprintf(text[0],"%ld : Altitude:%.0f", gps_count, points.now.height);
      lcd_clear();
      lcd_str(text[0]);
      
   }while(fall == 1 && gps_count < 300);
   
   fprintf(xbee,"Parachute is opened\r\n");
   sprintf(text[0],"Parachute is opened");
   lcd_clear();
   lcd_str(text[0]);

   // set start coordinates

   points.start.latitude = get_latitude(buffer);
   points.start.longitude = get_longitude(buffer);
   points.start.height = get_height(buffer);
   
   // pin wait
   for(int i = 0; i <= pin_wait; i++){
      gets(buffer);
      gps_count++;
      fprintf(xbee,"%ld : Altitude:%.0f,CountDown:%ld\r\n",gps_count, points.now.height, pin_wait - i);
      sprintf(text[0],"%ld : Altitude:%.0f",gps_count, points.now.height);
      sprintf(text[1],"Count:%ld",pin_wait - i);
      lcd_clear();
      lcd_str(text[0]);
      lcd_cmd(0xC0);
      lcd_str(text[1]);
      
      if(i == (pin_wait - 1)){
       fprintf(xbee,"Servo On\r\n"); 
         // Servo On  duty 7.4% = 90deg (open)
         for(int survo=0; survo < 25; survo++){
            output_high(PIN_B5);
            delay_us(1480);
            output_low(PIN_B5);
            delay_us(18520);
         }
         gets(buffer);
         // duty 12% =  180deg
         for(int survo = 0; survo < 25; survo++){
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
   sprintf(text[1],"Target:%4.0f,%4.0f",points.goal.longitude, points.goal.latitude);
   lcd_clear();
   lcd_str(text[0]);
   lcd_cmd(0xC0);
   lcd_str(text[1]);
   fprintf(xbee,"Target:%4.0f,%4.0f \r\n",points.goal.longitude, points.goal.latitude);
   forword(&pins);
   gps_count = 1;

   // Keep distance from parachute
   for(int i = 0; i < 12; i++){
      gets(buffer);
      fprintf(xbee,"Forward %ld \r\n",gps_count);
      gps_count++;
   }
   // end fall part


   bool check = false;
   int count = 0;
   int direction = 10;
   float dist, angle;
   product *prod;
   
   // start to go to points.goal
   // loop -------------------------------------------------------------------
   while(1){ 
      get_counts(&points, buffer, gps, gps_count);
      dist = calc_dist(&points);
      angle = calc_angle(&points, prod);
      turn_check(&motor_time, &gps_angle, &pins, angle, prod->cross, direction, count);
      back_check(&points, &pins, check, count);
      
      if(direction > 15){
         left_turn(&pins);
         for(int i = 0; i < 6; i++){
            delay_ms(250);
         }
         direction = 10;
         fprintf(xbee,"turn left\r\n");
      }else if(direction < 5){
         stop(&pins);
         gets(buffer);
         right_turn(&pins);
         for(int i = 0; i < 3; i++){
            delay_ms(250);
         }
         stop(&pins);
         gets(buffer);
         right_turn(&pins);
         for(int i = 0; i < 3; i++){
            delay_ms(250);
         }
         direction = 10;
         fprintf(xbee,"turn right\r\n");
      }
      
      // print to log file
      fprintf(xbee,"%ld : %4.0f, %4.0f DIST:%.0f ANGLE:%.0f L:%ld R:%ld direction = %d \r\n",gps_count, points.now.longitude, points.now.latitude, dist, angle, gps_angle.left, gps_angle.right, direction);
      sprintf(text[0],"%4.0f DIST:%f ANGLE:%f",points.now.longitude ,dist, angle);
      sprintf(text[1],"%4.0f L:%ld,R:%ld,direction = %d", points.now.latitude, gps_angle.left, gps_angle.right, direction);
      lcd_clear();
      lcd_str(text[0]);
      lcd_cmd(0xC0);
      lcd_str(text[1]);
      if(count != 0 && check == 0){ 
         forword(&pins);
      }else if(count == 6){
         count = 0;
      }else if(dist < 10){    // 10m以内に到着
         stop(&pins);
         fprintf(xbee,"Arrived Goal within 10m\r\n");
         break;
      }else{
         count++;
      }
      // end loop
   }
   stop(&pins);
   // end
}
