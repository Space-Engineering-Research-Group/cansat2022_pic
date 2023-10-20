#include <18f32520.h>
#fuses HS,NOWDT,NOPROTECT,PUT,BROWNOUT,NOLVP

#include <stack_check.c>
#include <get_gps.c>
#include <motor.c>
#include <calculate.c>

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)

// RS232 setup
#use delay(CLOCK=20000000)

// GPS setup
#use rs232(Baud=9600, XMIT=PIN_C6, RCV=PIN_C7, stream=gps, ERRORS)sbe

// xbee setup
#use rs232(Baud=9600, XMIT=PIN_B2, RCV=PIN_B3, stream=xbee)
#use i2c(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#byte UCFG = 0xF6F
#bit UTRDIS = UCFG.3

void main(void) 
{

    // USB disable
    UTRDIS = 1;    

    // initial setup
    set_tirs_a(0x00);
    set_tirs_b(0x18);
    set_tirs_c(0x80);

    // pins setup
    AllPins motor_pin;
    motor_pin.Left.forward  = PIN_C0;
    motor_pin.Left.back     = PIN_C1;
    motor_pin.Right.forward = PIN_A0;
    motor_pin.Right.back    = PIN_C2;

    // motor stop
    motor_stop(&motor_pin);
    
    // TODO: setup code
    
    // TODO: test code
}