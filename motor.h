struct MotorPin
{
    int forward;
    int back;
};


struct AllPins
{
    struct MotorPin Right;
    struct MotorPin Left;
};


/// @brief turn right
/// @param motor_pin motor pins 
void motor_right_turn(struct AllPins);

/// @brief turn left
/// @param motor_pin motor pins 
void motor_left_turn(struct AllPins);

/// @brief stop
/// @param motor_pin motor pins 
void motor_stop(struct AllPins);

/// @brief forward
/// @param motor_pin motor pins 
void motor_forward(struct AllPins);

/// @brief back
/// @param motor_pin motor pins 
void motor_back(struct AllPins);

/// @brief right rotate
/// @param motor_pin motor pins 
void motor_right_rotate(struct AllPins);

/// @brief left rotate
/// @param motor_pin motor pins 
void motor_left_rotate(struct AllPins);
