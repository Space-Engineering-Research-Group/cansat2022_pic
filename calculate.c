#include <calculate.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
} Vector;

double distance(double x, double y){
    return sqrt(x*x + y*y);
}

double cross_product(Vector *a, Vector *b) {
    return a->x_component * b->y_component + a->y_component * b->x_component;
}

double inner_product(Vector *a, Vector *b) {
    return a->x_component * b->x_component + a->y_component * b->y_component;
}

double calculate_angle(double inner_product) {
    return acos(inner_product) / acos(-1.0);
}