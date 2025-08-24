#ifndef EQUATION_STRUCT_H
#define EQUATION_STRUCT_H


struct square_equation_data
{
    double a;
    double b;
    double c;
    double* root_1;
    double* root_2;
    root_number number_of_roots;
};

void initialise_data(square_equation_data data);


#endif
