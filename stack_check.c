#include <math.h>
#include <stack_check.h>
#include <motor.c>
#include <get_gps.c>
#include <calculate.c>

// RS232 setup
#use delay(CLOCK=20000000)

// xbee setup
#use rs232(Baud=9600, XMIT=PIN_B2, RCV=PIN_B3, stream=xbee)
#byte UCFG = 0xF6F
#bit UTRDIS = UCFG.3

void back_check(struct Coordinate *current, struct Coordinate *initial, struct AllPins *motorpin){
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

void turn_check(struct Coordinate *current_coordinate, struct Coordinate *initial_coordinate, struct Coordinate *goal_coordinate, struct AllPins *motor_pin) {
    struct Vector current_vector, goal_vector;

    current_vector.x = current_coordinate->latitude - initial_coordinate->latitude;
    current_vector.y = current_coordinate->longitude - initial_coordinate->longitude;

    goal_vector.x = goal_coordinate->latitude - initial_coordinate->latitude;
    goal_vector.y = goal_coordinate->longitude - initial_coordinate->longitude;

    double to_goal_inner = inner_product(current_vector, goal_vector);
    double to_goal_cross = cross_product(current_vector, goal_vector);

    double to_goal_angle = calculate_angle(to_goal_inner);

    float turn_left_time_per_angle = 1700.00;

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
