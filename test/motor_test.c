#include "../motor.c"
#include<18f2520.h>

#use fast_io(C)
#use delay(CLOCK=20000000)


void main(void) {

    // set up output pins
    // A0 is output mocde
    // other ports are input mode
    set_tris_a(0xFE);

    // All of C ports are output mode
    set_tris_c(0x00);

    AllPins *motor_pin;

    motor_pin->Left.forward     = PIN_C0;
    motor_pin->Left.back        = PIN_C1;
    motor_pin->Right.forward    = PIN_A0;
    motor_pin->Right.back       = PIN_C2;

    motor_stop(motor_pin);
    delay_ms(1000);

    motor_left_turn(motor_pin);
    delay_ms(1000);

    motor_right_turn(motor_pin);
    delay_ms(1000);

    motor_forward(motor_pin);
    delay_ms(1000);

    motor_back(motor_pin);
    delay_ms(1000);

    motor_left_rotate(motor_pin);
    delay_ms(1000);

    motor_right_rotate(motor_pin);
    delay_ms(1000);

    motor_stop(motor_pin);
}
