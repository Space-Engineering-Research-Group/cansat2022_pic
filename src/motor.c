typedef struct {
   int right[2];
   int left[2];
} Motor_Pin;

void left_turn(Motor_Pin *motor){
   delay_ms(1);
   
   output_high(motor->right[0]);
   output_low(motor->right[1]);
   
   output_low(motor->left[0]);
   output_low(motor->left[1]);
}

void right_turn(Motor_Pin *motor){
   delay_ms(1);
   
   output_low(motor->right[0]);
   output_low(motor->right[1]);
   
   output_high(motor->left[0]);
   output_low(motor->left[1]);
}

void stop(Motor_Pin *motor){
   output_low(motor->right[0]);
   output_low(motor->right[1]);
   
   output_low(motor->left[0]);
   output_low(motor->left[1]);
}

void forward(Motor_Pin *motor){
   delay_ms(1);
   output_low(motor->right[0]);
   output_high(motor->right[1]);
   
   output_low(motor->left[0]);
   output_high(motor->left[1]);
}

void back(Motor_Pin *motor){
   delay_ms(1);
   output_high(motor->right[0]);
   output_low(motor->right[1]);
   
   output_high(motor->left[0]);
   output_low(motor->left[1]);
}

void right_rotate(Motor_Pin *motor){
   delay_ms(1);
   output_low(motor->right[0]);
   output_high(motor->right[1]);
   
   output_high(motor->left[0]);
   output_low(motor->left[1]);
}

void left_rotate(Motor_Pin *motor){
   delay_ms(1);
   output_high(motor->right[0]);
   output_low(motor->right[1]);
   
   output_low(motor->left[0]);
   output_high(motor->left[1]);
}

