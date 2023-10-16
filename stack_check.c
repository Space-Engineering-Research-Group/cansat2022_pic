#include <math.h>
#include <calculate.h>
#include <motor.h>
#include <stack_check.h>
#include <get_gps.h>

typedef struct
{
    double longitude;
    double latitude;
} Coordinate;

void back_check(Coordinate *current, Coordinate *initial, AllPins *motorpin){
    double distance_advanced = distance(current->latitude, current->longitude) - distance(initial->latitude, initial->longitude);
    if(fabs(distance_advanced) < 0.0005){
        fprintf(xbee, "Back initial\r\n");
        motor_back(motorpin);
        delay_ms(1000);
    } else {
        return;
    }
    motor_right_rotate(motorpin);
    delay_ms(1000);
}

void turn_check(Coordinate *current_coordinate, Coordinate *initial_coordinate, Coordinate *goal_coordinate, AllPins *motor_pin) {
    Vector *current_vector, *initial_vector, *goal_vector;

    current_vector->x = current_coordinate->latitude - initial_coordinate->latitude;
    current_vector->y = current_coordinate->longitude - initial_coordinate->longitude;

    goal_vector->x = goal_coordinate->latitude - initial_coordinate->latitude;
    goal_vector->y = goal_coordinate->longitude - initial_coordinate->longitude;

    double to_goal_inner = inner_product(current_vector, goal_vector);
    double to_goal_cross = cross_product(current_vector, goal_vector);

    double to_goal_angle = calculate_angle(to_goal_inner);

    float turn_left_time_per_angle = 1700.00;
    float turn_right_time_per_angle = 1700.00;

    if(to_goal_cross < 0 && to_goal_angle > 0.05) {
        int turn_time = turn_left_time_per_angle * to_goal_angle;
        motor_left_turn(motor_pin);
        delay_ms(turn_time);
        motor_forward(motor_pin);
    } else if(to_goal_cross > 0 && to_goal_angle > 0.05) {
        int turn_time = turn_left_time_per_angle * to_goal_angle;
        motor_right_turn(motor_pin);
        delay_ms(turn_time);
        motor_forward(motor_pin);
    }
    return;
}