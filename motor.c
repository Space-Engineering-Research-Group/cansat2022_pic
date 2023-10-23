#include<motor.h>

void motor_left_turn(struct AllPins *all_pins)
{
   output_high(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   
   output_low(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_right_turn(struct AllPins *all_pins)
{
   output_low(all_pins->Left.forward);
   output_low(all_pins->Left.back);

   output_high(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_stop(struct AllPins *all_pins)
{
   output_low(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   
   output_low(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_forward(struct AllPins *all_pins)
{
   output_high(all_pins->Left.forward);
   output_low(all_pins->Left.back);

   output_high(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_back(struct AllPins *all_pins)
{
   output_low(all_pins->Left.forward);
   output_high(all_pins->Left.back);

   output_low(all_pins->Right.forward);
   output_high(all_pins->Right.back);
}

void motor_right_rotate(struct AllPins *all_pins)
{
   output_low(all_pins->Left.forward);
   output_high(all_pins->Left.back);
   
   output_high(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_left_rotate(struct AllPins *all_pins)
{
   output_high(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   
   output_low(all_pins->Right.forward);
   output_high(all_pins->Right.back);
}
