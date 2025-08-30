#ifndef SOLVING_MODULE_H
#define SOLVING_MODULE_H


#define A_KOEF data -> a
#define B_KOEF data -> b
#define C_KOEF data -> c


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


struct quadratic_equation_data
{
    const double a;
    const double b;
    const double c;
    double root_1;
    double root_2;
};


const double EPSILON = 10e-3;


root_number solve_equation(quadratic_equation_data* const data);
bool is_equal(double a, double b);
void run_tests(char file[]);


#endif
