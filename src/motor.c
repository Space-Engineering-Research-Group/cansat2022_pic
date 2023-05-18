#include <stdio.h>

struct Motor_Pin {
   int left;
   int right;
};

struct Pins {
   struct Motor_Pin forword;
   struct Motor_Pin back;
};

void left_turn(struct Pins *pins){
   delay_ms(1);
   
   output_high(pins->forword.right);
   output_low(pins->back.right);
   
   output_low(pins->forword.left);
   output_low(pins->back.left);
}

void right_turn(struct Pins *pins){
   delay_ms(1);
   
   output_low(pins->forword.right);
   output_low(pins->back.right);
   
   output_high(pins->forword.left);
   output_low(pins->back.left);
}

void stop(struct Pins *pins){
   output_low(pins->forword.right);
   output_low(pins->back.right);
   
   output_low(pins->forword.left);
   output_low(pins->back.left);
}

void forword(struct Pins *pins){
   delay_ms(1);
   output_low(pins->forword.right);
   output_high(pins->back.right);
   
   output_low(pins->forword.left);
   output_high(pins->back.left);
}

void back(struct Pins *pins){
   delay_ms(1);
   output_high(pins->forword.right);
   output_low(pins->back.right);
   
   output_high(pins->forword.left);
   output_low(pins->back.left);
}

void right_rotate(struct Pins *pins){
   delay_ms(1);
   output_low(pins->forword.right);
   output_high(pins->back.right);
   
   output_high(pins->forword.left);
   output_low(pins->back.left);
}

void left_rotate(struct Pins *pins){
   delay_ms(1);
   output_high(pins->forword.right);
   output_low(pins->back.right);
   
   output_low(pins->forword.left);
   output_high(pins->back.left);
}

