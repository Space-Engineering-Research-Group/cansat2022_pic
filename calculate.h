#ifndef CALCULATE_H
#define CALCULATE_H

typedef struct
{
    double x;
    double y;
} Vector;

/// @brief calcurate distance
/// @param x x is decalt of x point
/// @param y y is decalt of y poiht
/// @return sqrt(x^2 + y^2)
double distance(double, double);

/// @brief calcurate cross product
/// @param vector_a a vector
/// @param vector_b b vector
/// @return a x b
double cross_product(Vector, Vector);

/// @brief calcurate inner product
/// @param vector_a a vector 
/// @param vector_b b vector
/// @return a ・ b
double inner_product(Vector, Vector);

/// @brief calculate from inner product
/// @param inner_product value of inner product
/// @return angle
double calculate_angle(double);

#endif