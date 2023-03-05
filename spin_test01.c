#include <18f252.h>

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
#use rs232(Baud = 4800, XMIT = PIN_C6, RCV = PIN_C7)
#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3, SLOW)
//#include <navi_lib.c>
#include <spin.c>

void main()
{   
// Motor setup
   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_1,0xFF,1);
   setup_ccp2(CCP_PWM);
   setup_timer_2(T2_DIV_BY_1,0xFF,1);
   
   stop();

//int1 land=1; // landing flug ; 0=sleep, 1=run

   set_tris_A(0x00); //A port output mode
   set_tris_B(0x00); //B port output mode
   set_tris_C(0x00); //C port output mode
   
   right_turn();
   delay_ms(1700);
   left_turn();
   delay_ms(1700);
   stop();
   delay_ms(1000);
   


}

