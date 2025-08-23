#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

// rename and delete UNKNOWN_ERROR
enum root_number
{
    TWO_ROOTS = 2,
    ONE_ROOT = 1,
    NO_ROOTS = 0,
    INF = -1,
    UNKNOWN_NUMBER = -2
};

enum program_states {ON = 1, OFF = 0};

const double EPSILON = 10e-3;

root_number solve_square_equation(double a, double b, double c, double* root_1, double* root_2);
root_number solve_linear_equation(double b, double c, double* root_1);
root_number solve_equation(double a, double b, double c, double* root_1, double* root_2);
void get_koef(double* a, double* b, double* c);
void print_ans(root_number number_of_roots, double root_1, double root_2);
void clear_buffer(void);
double calculate_discriminant(double a, double b, double c);
int is_equal(double a, double b);
int is_zero(double n);
int check_buffer();
void check_new_equations(int* state);


// TODO: unit tests
// TODO: assert equal pointers
// TODO: sqrt
// TODO: bool

int main()
{
    double a_koef = 0, b_koef = 0, c_koef = 0;
    int program_state = ON;

    printf("+++ Square Equation Solver +++\n");

    root_number number_of_roots = NO_ROOTS;

    while (program_state) // TODO: comparison
    {
        get_koef(&a_koef, &b_koef, &c_koef);

        double root_1 = 0, root_2 = 0;
        number_of_roots = solve_equation(a_koef, b_koef, c_koef, &root_1, &root_2);

        print_ans(number_of_roots, root_1, root_2);

        check_new_equations(&program_state);
    }
    return 0;
}


void check_new_equations(int* state)
{
    printf("Any new equations? (no - 0, yes - 1): ");

    int ans = 0;
    int correct_input = scanf("%d", &ans);
    while (correct_input != 1 || !check_buffer())
    {
        printf("Wrong input. Please try again:\n");
        clear_buffer();
        correct_input = scanf("%d", &ans);
    }

    if (ans)
        *state = ON;
    else
    {
        *state = OFF;
        printf("I\'ll be back...\n");
    }
}


void clear_buffer(void)
{
    int c = '\0';
    while ((c = getchar()) != '\n' && c != EOF);
}


int check_buffer()
{
    int c = getchar();
    return c == EOF || c == '\n';
}


void get_koef(double* a, double* b, double* c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    printf("Enter a, b, c parameters for equation ax^2 + bx + c = 0:\n");

    int correct_koef_number = scanf("%lf %lf %lf", a, b, c);
    while (correct_koef_number != 3 || !check_buffer())
    {
        printf("Wrong input. Please try again:\n");
        clear_buffer();
        correct_koef_number = scanf("%lf %lf %lf", a, b, c);
    }
}


void print_ans(root_number number_of_roots, double root_1, double root_2)
{
    // isfinite
    assert(!isinf(root_1));
    assert(!isinf(root_2));

    switch (number_of_roots)
    {
        case NO_ROOTS:
            printf("This equation does not have any roots\n");
            break;
        case ONE_ROOT:
            printf("This equation has 1 root:\n");
            printf("x = %lf\n", root_1);
            break;
        case TWO_ROOTS:
            printf("This equation has 2 roots:\n");
            printf("x1 = %lf, x2 = %lf\n", root_1, root_2);
            break;
        case INF:
            printf("This equation has infinite number of roots\n");
            break;
        case UNKNOWN_NUMBER:
            printf("Unexpected error");
    }
}


// bx + c = 0
root_number solve_linear_equation(double b, double c, double* root)
{
    assert(root != NULL);
    assert(!isinf(b));
    assert(!isinf(c));

    if (is_zero(b))
    {
        if (is_zero(c))
            return INF;
        return NO_ROOTS;
    }
    else
    {
        *root = -c / b;
        return ONE_ROOT;
    }
}


double calculate_discriminant(double a, double b, double c)
{
    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));

    double d = b * b - 4 * a * c;
    return d;
}


// ax^2 + bx + c = 0
root_number solve_square_equation(double a, double b, double c, double* root_1, double* root_2)
{
    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));
    assert(root_1 != NULL);
    assert(root_2 != NULL);
    assert(!is_zero(a));

    double discriminant = calculate_discriminant(a, b, c);

    if (discriminant < 0)
    {
        return NO_ROOTS;
    }
    else if (is_zero(discriminant))
    {
        *root_1 = -b / (2 * a);
        return ONE_ROOT;
    }
    else if (discriminant > 0)
    {
        *root_1 = (-b - sqrt(discriminant)) / (2 * a);
        *root_2 = (-b + sqrt(discriminant)) / (2 * a);
        return TWO_ROOTS;
    }
    else
        return UNKNOWN_NUMBER;
}


root_number solve_equation(double a, double b, double c, double* root_1, double* root_2)
{
    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));
    assert(root_1 != NULL);
    assert(root_2 != NULL);

    root_number number_of_roots = NO_ROOTS;

    if (is_zero(a))
        number_of_roots = solve_linear_equation(b, c, root_1);
    else
        number_of_roots = solve_square_equation(a, b, c, root_1, root_2);

    return number_of_roots;
}


int is_zero(double n)
{
    assert(!isinf(n));

    return is_equal(n, 0.0);
}

int is_equal(double a, double b)
{
    assert(!isinf(a));
    assert(!isinf(b));

    return fabs(a - b) < EPSILON; // 10e-3
}
