void right_turn(void);
void left_turn(void);
void stop(void);
void forward(void);
void back(void);
void right_rotate(void);
void left_rotate(void)

typedef struct
{
   int forward;
   int back;
} MotorPin;

struct AllPins
{
   MotorPin Right;
   MotorPin Left;
} all_pins;


void left_turn(void)
{
   delay_ms(1);
   
   output_high(all_pins.Left.forward);
   output_low(all_pins.Left.back);
   
   output_low(all_pins.Right.forward);
   output_low(all_pins.Right.back);
}

void right_turn(void)
{
   delay_ms(1);
   
   output_low(all_pins.Left.forward);
   output_low(all_pins.Left.back);
   
   output_high(all_pins.Right.forward);
   output_low(all_pins.Right.back);
}

void stop(void)
{
   output_low(all_pins.Left.forward);
   output_low(all_pins.Left.back);
   
   output_low(all_pins.Right.forward);
   output_low(all_pins.Right.back);
}

void forward(void)
{
   delay_ms(1);
   output_low(all_pins.Left.forward);
   output_high(all_pins.Left.back);
   
   output_low(all_pins.Right.forward);
   output_high(all_pins.Right.back);

}

void back(void)
{
   delay_ms(1);
   output_high(all_pins.Left.forward);
   output_low(all_pins.Left.back);
   
   output_high(all_pins.Right.forward);
   output_low(all_pins.Right.back);
}

void right_rotate(void)
{
   delay_ms(1);
   output_low(all_pins.Left.forward);
   output_high(all_pins.Left.back);
   
   output_high(all_pins.Right.forward);
   output_low(all_pins.Right.back);
}

void left_rotate(void)
{
   delay_ms(1);
   output_high(all_pins.Left.forward);
   output_low(all_pins.Left.back);
   
   output_low(all_pins.Right.forward);
   output_high(all_pins.Right.back);
}

