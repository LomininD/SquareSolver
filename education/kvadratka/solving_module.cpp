#include "solving_module.h"


// TODO: arrays (or structs)
// TODO: loop in unit test (after structs)
// TODO: add const qualifiers to func parameters where necessary
// TODO: reorder functions
// TODO: add unit test (after structs)
// TODO: delete pointers in test (after structs)
// TODO: delete pointers in programm state


// bx + c = 0
root_number solve_linear_equation(square_equation_data* data)
{
    assert(data != NULL);
    assert(isfinite((*data).b));
    assert(isfinite((*data).c));
    assert(isfinite((*data).root_1));

    double b = (*data).b;
    double c = (*data).c;

    if (is_zero(b))
    {
        if (is_zero(c))
            return INF_ROOTS;
        return NO_ROOTS;
    }
    else
    {
        double raw_root = -c / b;
        (*data).root_1 = inspect_zero_root(raw_root);
        return ONE_ROOT;
    }
}


double inspect_zero_root(double raw_root)
{
    if (is_zero(raw_root))
            raw_root = 0.0;
    return raw_root;
}


double calculate_discriminant(double a, double b, double c)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double d = b * b - 4 * a * c;
    return d;
}


// ax^2 + bx + c = 0
root_number solve_square_equation(square_equation_data* data)
{
    assert(isfinite((*data).a));
    assert(isfinite((*data).b));
    assert(isfinite((*data).c));
    assert(isfinite((*data).root_1));
    assert(isfinite((*data).root_2));
    assert(data != NULL);

    double a = (*data).a;
    double b = (*data).b;
    double c = (*data).c;


    double discriminant = calculate_discriminant(a, b, c);

    if (discriminant < 0)
    {
        return NO_ROOTS;
    }
    else if (is_zero(discriminant))
    {
        double raw_root = -b / (2 * a);
        (*data).root_1 = inspect_zero_root(raw_root);
        return ONE_ROOT;
    }
    else // if (discriminant > 0)
    {
        double sqrt_discr = sqrt(discriminant);

        double raw_root1 = (-b - sqrt_discr) / (2 * a);
        double raw_root2 = (-b + sqrt_discr) / (2 * a);

        (*data).root_1 = inspect_zero_root(raw_root1);
        (*data).root_2 = inspect_zero_root(raw_root2);
        return TWO_ROOTS;
    }
}


root_number solve_equation(square_equation_data* data)
{
    assert(isfinite((*data).a));
    assert(isfinite((*data).b));
    assert(isfinite((*data).c));
    assert(isfinite((*data).root_1)); // TODO: !!!
    assert(isfinite((*data).root_2));
    assert(data != NULL);

    root_number number_of_roots = NO_ROOTS;

    if (is_zero((*data).a))
        number_of_roots = solve_linear_equation(data);
    else
        number_of_roots = solve_square_equation(data);
    return number_of_roots;
}


bool is_zero(double n)
{
    if (!isfinite(n))
        return false;

    return is_equal(n, 0.0);
}


bool is_equal(double a, double b)
{
    assert(isfinite(a));
    assert(isfinite(b));

    return fabs(a - b) < EPSILON; // 10e-3
}


