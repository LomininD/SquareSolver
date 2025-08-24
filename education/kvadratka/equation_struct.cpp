#include "equation_struct.h"


void initialise_data(square_equation_data data, double* root_1, double* root_2)
{
    data.a = 0;
    data.b = 0;
    data.c = 0;
    data.number_of_roots = NO_ROOTS;
    data.root_1 = root_1;
    data.root_2 = root_2;
}
