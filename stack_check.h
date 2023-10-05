#ifndef STACKCHECK_H
#define STACKCHECK_H

typedef sturct
{
    double longitude;
    double latitude;
} Coordinate;

/// @brief function to back up when hitting an obstacle
/// @param now coordinate of now  
/// @param start coordinate of start 
/// @param motor_pin motor pins 
void back_check(Coordinate, Coordinate, AllPins);

/// @brief function to correct and proceed if the line to the goal is misaligned
/// @param now_coordinate Current coordinate
/// @param start_coordinate initial coordinate 
/// @param goal_coordinate goal coordinate
/// @param motor_pin motor pins
void turn_check(Coordinate, Coordinate, Coordinate, AllPins);

#endif