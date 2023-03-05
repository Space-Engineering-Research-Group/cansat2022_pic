
void left_turn(void)
{
   delay_ms(1);
   
   output_high(PIN_C0);
   output_low(PIN_C1);
   
   output_low(PIN_A0);
   output_low(PIN_C2);
}

void right_turn(void)
{
   delay_ms(1);
   
   output_low(PIN_C0);
   output_low(PIN_C1);
   
   output_high(PIN_A0);
   output_low(PIN_C2);
}

void stop(void)
{
   output_low(PIN_C0);
   output_low(PIN_C1);
   
   output_low(PIN_A0);
   output_low(PIN_C2);
}

void forward(void)
{
   delay_ms(1);
   output_low(PIN_C0);
   output_high(PIN_C1);
   
   output_low(PIN_A0);
   output_high(PIN_C2);

}

void back(void)
{
   delay_ms(1);
   output_high(PIN_C0);
   output_low(PIN_C1);
   
   output_high(PIN_A0);
   output_low(PIN_C2);
}

void right_rotate(void)
{
   delay_ms(1);
   output_low(PIN_C0);
   output_high(PIN_C1);
   
   output_high(PIN_A0);
   output_low(PIN_C2);
}

void left_rotate(void)
{
   delay_ms(1);
   output_high(PIN_C0);
   output_low(PIN_C1);
   
   output_low(PIN_A0);
   output_high(PIN_C2);
}

