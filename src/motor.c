#include <stdio.h>

struct Motor_Pin {
   int left;
   int right;
};

struct Pins {
   struct Motor_Pin forword;
   struct Motor_Pin back;
};

/// @brief turn left
/// @param pins motor pin
void left_turn(struct Pins *pins){
   delay_ms(1);
   
   output_high(pins->forword.right);
   output_low(pins->back.right);
   
   output_low(pins->forword.left);
   output_low(pins->back.left);
}

/// @brief turn right
/// @param pins motor pin
void right_turn(struct Pins *pins){
   delay_ms(1);
   
   output_low(pins->forword.right);
   output_low(pins->back.right);
   
   output_high(pins->forword.left);
   output_low(pins->back.left);
}

/// @brief run stop
/// @param pins motor pin
void stop(struct Pins *pins){
   output_low(pins->forword.right);
   output_low(pins->back.right);
   
   output_low(pins->forword.left);
   output_low(pins->back.left);
}

/// @brief run forword
/// @param pins motor pin
void forword(struct Pins *pins){
   delay_ms(1);
   output_low(pins->forword.right);
   output_high(pins->back.right);
   
   output_low(pins->forword.left);
   output_high(pins->back.left);
}

/// @brief run back
/// @param pins motor pin
void back(struct Pins *pins){
   delay_ms(1);
   output_high(pins->forword.right);
   output_low(pins->back.right);
   
   output_high(pins->forword.left);
   output_low(pins->back.left);
}

/// @brief right rotate
/// @param pins motor pin
void right_rotate(struct Pins *pins){
   delay_ms(1);
   output_low(pins->forword.right);
   output_high(pins->back.right);
   
   output_high(pins->forword.left);
   output_low(pins->back.left);
}

/// @brief left rotate
/// @param pins motor pin
void left_rotate(struct Pins *pins){
   delay_ms(1);
   output_high(pins->forword.right);
   output_low(pins->back.right);
   
   output_low(pins->forword.left);
   output_high(pins->back.left);
}

