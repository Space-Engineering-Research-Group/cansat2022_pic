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

/// @brief turn right
/// @param motor_pin motor pins 
void motor_right_turn(AllPins);

/// @brief turn left
/// @param motor_pin motor pins 
void motor_left_turn(AllPins);

/// @brief stop
/// @param motor_pin motor pins 
void motor_stop(AllPins);

/// @brief forward
/// @param motor_pin motor pins 
void motor_forward(AllPins);

/// @brief back
/// @param motor_pin motor pins 
void motor_back(AllPins);

/// @brief right rotate
/// @param motor_pin motor pins 
void motor_right_rotate(AllPins);

/// @brief left rotate
/// @param motor_pin motor pins 
void motor_left_rotate(AllPins);