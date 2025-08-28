#include "solving_module.h"


#define ROOT_1 data -> root_1
#define ROOT_2 data -> root_2


// TODO: reorder function declaration
// TODO: doxygen
// TODO: README
// TODO: diagram for readme (drawio)


static double calculate_discriminant(double a, double b, double c);
static bool is_zero(double n);
static double inspect_zero_root(double raw_root);
static root_number solve_quadratic_equation(quadratic_equation_data* const data);
static root_number solve_linear_equation(quadratic_equation_data* const data);


root_number solve_equation(quadratic_equation_data* const data)
{
    assert(data != NULL);
    assert(isfinite(A_KOEF));

    root_number number_of_roots = NO_ROOTS;

    if (is_zero(A_KOEF))
        number_of_roots = solve_linear_equation(data);
    else
        number_of_roots = solve_quadratic_equation(data);
    return number_of_roots;
}


// ax^2 + bx + c = 0
static root_number solve_quadratic_equation(quadratic_equation_data* const data)
{
    assert(data != NULL);
    assert(isfinite(A_KOEF));
    assert(isfinite(B_KOEF));
    assert(isfinite(C_KOEF));

    double discriminant = calculate_discriminant(A_KOEF, B_KOEF, C_KOEF);

    if (discriminant < 0)
    {
        return NO_ROOTS;
    }
    else if (is_zero(discriminant))
    {
        double raw_root = -B_KOEF / (2 * A_KOEF);
        ROOT_1 = inspect_zero_root(raw_root);
        return ONE_ROOT;
    }
    else // if (discriminant > 0)
    {
        double sqrt_discr = sqrt(discriminant);

        double raw_root1 = (-B_KOEF - sqrt_discr) / (2 * A_KOEF);
        double raw_root2 = (-B_KOEF + sqrt_discr) / (2 * A_KOEF);

        ROOT_1 = inspect_zero_root(raw_root1);
        ROOT_2 = inspect_zero_root(raw_root2);
        return TWO_ROOTS;
    }
}


// bx + c = 0
static root_number solve_linear_equation(quadratic_equation_data* const data)
{
    assert(data != NULL);
    assert(isfinite(B_KOEF));
    assert(isfinite(C_KOEF));

    if (is_zero(B_KOEF))
    {
        if (is_zero(C_KOEF))
            return INF_ROOTS;
        return NO_ROOTS;
    }
    else
    {
        double raw_root = -C_KOEF / B_KOEF;
        ROOT_1 = inspect_zero_root(raw_root);
        return ONE_ROOT;
    }
}


static double calculate_discriminant(double a, double b, double c)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double d = b * b - 4 * a * c;
    return d;
}


static double inspect_zero_root(double raw_root)
{
    if (is_zero(raw_root))
            raw_root = 0.0;
    return raw_root;
}


bool is_equal(double a, double b)
{
    assert(isfinite(a));
    assert(isfinite(b));

    return fabs(a - b) < EPSILON; // 10e-3
}


static bool is_zero(double n)
{
    if (!isfinite(n))
        return false;

    return is_equal(n, 0.0);
}
