void right_turn(AllPins *all_pins);
void left_turn(AllPins *all_pins);
void stop(AllPins *all_pins);
void forward(AllPins *all_pins);
void back(AllPins *all_pins);
void right_rotate(AllPins *all_pins);
void left_rotate(AllPins *all_pins)

typedef struct
{
   int forward;
   int back;
} MotorPin;

typedef struct
{
   MotorPin Right;
   MotorPin Left;
} AllPins;


void motor_left_turn(AllPins *all_pins)
{
   delay_ms(1);
   
   output_high(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   
   output_low(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_right_turn(AllPins *all_pins)
{
   delay_ms(1);
   output_low(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   output_high(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_stop(AllPins *all_pins)
{
   output_low(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   
   output_low(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_forward(AllPins *all_pins)
{
   delay_ms(1);
   output_low(all_pins->Left.forward);
   output_high(all_pins->Left.back);
   
   output_low(all_pins->Right.forward);
   output_high(all_pins->Right.back);

}

void motor_back(AllPins *all_pins)
{
   delay_ms(1);
   output_high(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   
   output_high(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_right_rotate(AllPins *all_pins)
{
   delay_ms(1);
   output_low(all_pins->Left.forward);
   output_high(all_pins->Left.back);
   
   output_high(all_pins->Right.forward);
   output_low(all_pins->Right.back);
}

void motor_left_rotate(AllPins *all_pins)
{
   delay_ms(1);
   output_high(all_pins->Left.forward);
   output_low(all_pins->Left.back);
   
   output_low(all_pins->Right.forward);
   output_high(all_pins->Right.back);
}

