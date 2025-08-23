#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>


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
void read_koef(double* a, double* b, double* c);
void print_ans(root_number number_of_roots, double root_1, double root_2);
void clear_buffer(void);
double calculate_discriminant(double a, double b, double c);
bool is_equal(double a, double b);
bool is_zero(double n);
bool check_buffer();
void ask_for_new_equations(int* state);
void test_solve_equation(void);
void test(double a, double b, double c, root_number correct_number_of_roots, double correct_root_1, double correct_root_2, int* succeeded, int* max_succeeded);


//TODO: 3 files
//TODO: arrays
//TODO: loop in unit test
//TODO: add define to colored words


int main()
{
    double a_koef = 0, b_koef = 0, c_koef = 0;
    int program_state = ON;

    test_solve_equation();

    printf("+++ Square Equation Solver +++\n");

    root_number number_of_roots = NO_ROOTS;

    while (program_state == ON)
    {
        read_koef(&a_koef, &b_koef, &c_koef);

        double root_1 = 0, root_2 = 0;
        number_of_roots = solve_equation(a_koef, b_koef, c_koef, &root_1, &root_2);

        print_ans(number_of_roots, root_1, root_2);

        ask_for_new_equations(&program_state);
    }
    return 0;
}


void ask_for_new_equations(int* state)
{
    printf("Any new equations? (no - 0, yes - 1): ");

    int ans = 0;
    int correct_input = scanf("%d", &ans);
    while (correct_input != 1 || !check_buffer() || (ans != 0 && ans != 1))
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


bool check_buffer()
{
    int c = getchar();
    return c == EOF || c == '\n';
}


void read_koef(double* a, double* b, double* c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(a != b);
    assert(a != c);
    assert(b != c);

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
    assert(isfinite(root_1));
    assert(isfinite(root_2));

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
    assert(isfinite(b));
    assert(isfinite(c));

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
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double d = b * b - 4 * a * c;
    return d;
}


// ax^2 + bx + c = 0
root_number solve_square_equation(double a, double b, double c, double* root_1, double* root_2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(root_1 != NULL);
    assert(root_2 != NULL);
    assert(!is_zero(a));
    assert(root_1 != root_2);

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
        double sqrt_discr = sqrt(discriminant);
        *root_1 = (-b - sqrt_discr) / (2 * a);
        *root_2 = (-b + sqrt_discr) / (2 * a);
        return TWO_ROOTS;
    }
    else
        return UNKNOWN_NUMBER;
}


root_number solve_equation(double a, double b, double c, double* root_1, double* root_2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(root_1 != NULL);
    assert(root_2 != NULL);
    assert(root_1 != root_2);

    root_number number_of_roots = NO_ROOTS;

    if (is_zero(a))
        number_of_roots = solve_linear_equation(b, c, root_1);
    else
        number_of_roots = solve_square_equation(a, b, c, root_1, root_2);

    return number_of_roots;
}


bool is_zero(double n)
{
    assert(isfinite(n));

    return is_equal(n, 0.0);
}


bool is_equal(double a, double b)
{
    assert(isfinite(a));
    assert(isfinite(b));

    return fabs(a - b) < EPSILON; // 10e-3
}


void test(double a, double b, double c, root_number correct_number_of_roots, double correct_root_1, double correct_root_2, int* succeeded, int* max_succeeded)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(correct_root_1));
    assert(isfinite(correct_root_2));

    double root_1 = 0, root_2 = 0;

    *max_succeeded += 1;

    root_number number_of_roots = solve_equation(a, b, c, &root_1, &root_2);
    if (!(number_of_roots == correct_number_of_roots && is_equal(root_1, correct_root_1) && is_equal(root_2, correct_root_2)))
        printf("\033[1;31mFAILED\033[0m: solve_equation(%lf, %lf, %lf, &x1, &x2) --> roots: %d, x1 = %lf, x2 = %lf "
        "\n(should be roots: %d, x1 = %lf, x2 = %lf)\n", a, b, c, number_of_roots, root_1, root_2, correct_number_of_roots, correct_root_1, correct_root_2);
    else
    {
        printf("\033[1;32mOK\033[0m\n");
        *succeeded += 1;
    }
}


void test_solve_equation(void)
{
    int succeeded = 0, max_succeeded = 0;

    test(1, 2, 1, ONE_ROOT, -1, 0, &succeeded ,&max_succeeded);
    test(0, 0, 1, NO_ROOTS, 0, 0, &succeeded ,&max_succeeded);
    test(1, -5, 6, TWO_ROOTS, 2, 3, &succeeded ,&max_succeeded);
    test(0, 1, 2, ONE_ROOT, -2, 0, &succeeded ,&max_succeeded);
    test(0, 0, 0, INF, 0, 0, &succeeded ,&max_succeeded);
    test(1, 0, 0, ONE_ROOT, 0, 0, &succeeded ,&max_succeeded);
    test(5, 0, 0, ONE_ROOT, 0, 0, &succeeded ,&max_succeeded);
    test(0, 1, 0, ONE_ROOT, 0, 0, &succeeded ,&max_succeeded);
    test(1, 1, 0, TWO_ROOTS, -1, 0, &succeeded ,&max_succeeded);

    printf("\033[1mPassed %d/%d\033[0m\n", succeeded, max_succeeded);
}
