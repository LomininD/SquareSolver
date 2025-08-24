#ifndef SOLVING_MODULE_H
#define SOLVING_MODULE_H


#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>


enum root_number
{
    TWO_ROOTS = 2,
    ONE_ROOT = 1,
    NO_ROOTS = 0,
    INF_ROOTS = -1
};


const double EPSILON = 10e-3;

root_number solve_square_equation(double a, double b, double c, double* root_1, double* root_2);
root_number solve_linear_equation(double b, double c, double* root_1);
root_number solve_equation(double a, double b, double c, double* root_1, double* root_2);
double calculate_discriminant(double a, double b, double c);
bool is_equal(double a, double b);
bool is_zero(double n);
double inspect_zero_root(double raw_root);


#endif
