#include <calculate.h>
#include <math.h>

double distance(double x, double y){
    return sqrt(x*x + y*y);
}

double cross_product(struct Vector a, struct Vector b) {
    return a.x * b.y + a.y * b.x;
}

double inner_product(struct Vector a, struct Vector b) {
    return a.x * b.y - a.y * b.x;
}

double calculate_angle(double inner_product) {
    return acos(inner_product) / PI;
}