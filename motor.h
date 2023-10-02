#device PIC18F2520

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

void motor_right_turn(AllPins);
void motor_left_turn(AllPins);
void motor_stop(AllPins);
void motor_forward(AllPins);
void motor_back(AllPins);
void motor_right_rotate(AllPins);
void motor_left_rotate(AllPins);