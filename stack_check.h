#ifndef _STACKCHECK_H_
#define _STACKCHECK_H_

#include <motor.h>

struct Coordinate
{
    double longitude;
    double latitude;
};

/// @brief function to back up when hitting an obstacle
/// @param now coordinate of now  
/// @param start coordinate of start 
/// @param motor_pin motor pins 
void back_check(struct Coordinate, struct Coordinate, struct AllPins);

/// @brief function to correct and proceed if the line to the goal is misaligned
/// @param now_coordinate Current coordinate
/// @param start_coordinate initial coordinate 
/// @param goal_coordinate goal coordinate
/// @param motor_pin motor pins
void turn_check(struct Coordinate, struct Coordinate, struct Coordinate, struct AllPins);

#endif
