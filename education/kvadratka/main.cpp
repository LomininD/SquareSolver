#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

enum root_states {NO_ROOTS = 0,
                  INF = -1,
                  UNKNOWN_ERROR = -2};


int solve_square_equation(double a, double b, double c, double* root_1, double* root_2);
int solve_linear_equation(double b, double c, double root_1);
int solve_equation(double a, double b, double c, double* root_1, double* root_2);
void get_koef(double* a, double* b, double* c);
void print_ans(int number_of_roots, double root_1, double root_2);
void clear_buffer(void);
double calculate_discriminant(double a, double b, double c);
int is_equal(double a, double b);



// git hub


int main()
{
    double a_koef = 0, b_koef = 0, c_koef = 0, root_1 = 0, root_2 = 0;
    int number_of_roots = 0;

    get_koef(&a_koef, &b_koef, &c_koef);

    number_of_roots = solve_equation(a_koef, b_koef, c_koef, &root_1, &root_2);

    print_ans(number_of_roots, root_1, root_2);
    return 0;
}


void clear_buffer(void)
{
    int c = '\0';
    while ((c = getchar()) != '\n' && c != EOF);
}


void get_koef(double* a, double* b, double* c)
{
    int correct_koef_number = 0;

    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    printf("+++ Square Equation Solver +++\n");
    printf("Enter a, b, c parameters for equation ax^2 + bx + c = 0:\n");

    correct_koef_number = scanf("%lf %lf %lf", a, b, c);
    while (correct_koef_number != 3)
    {
        printf("Wrong input. Please try again:\n");
        clear_buffer();
        correct_koef_number = scanf("%lf %lf %lf", a, b, c);
    }
}


void print_ans(int number_of_roots, double root_1, double root_2)
{
    assert(!isinf(root_1));
    assert(!isinf(root_2));

    switch (number_of_roots)
    {
        case NO_ROOTS:
            printf("This equation does not have any roots\n");
            break;
        case 1:
            printf("This equation has 1 root:\n");
            printf("x = %lf\n", root_1);
            break;
        case 2:
            printf("This equation has 2 roots:\n");
            printf("x1 = %lf, x2 = %lf\n", root_1, root_2);
            break;
        case INF:
            printf("This equation has infinite number of roots\n");
            break;
        default:
            printf("Unexpected error");
    }
}


// bx + c = 0
int solve_linear_equation(double b, double c, double* root)
{
    assert(root != NULL);
    assert(!isinf(b));
    assert(!isinf(c));

    if (is_equal (b, (double) 0))
    {
        if (is_equal (c, (double) 0))
            return INF;
        return NO_ROOTS;
    }
    else
    {
        *root = -c / b;
        return 1;
    }
}


double calculate_discriminant(double a, double b, double c)
{
    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));

    double d = b*b - 4 * a*c;
    return d;
}


// ax^2 + bx + c = 0
int solve_square_equation(double a, double b, double c, double* root_1, double* root_2)
{
    double discriminant = 0;

    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));
    assert(root_1 != NULL);
    assert(root_2 != NULL);
    assert(a != 0); // isequal

    discriminant = calculate_discriminant(a, b, c);

    if (discriminant < 0)
    {
        return NO_ROOTS;
    }
    else if (is_equal (discriminant, (double) 0))
    {
        *root_1 = -b / (2 * a);
        return 1;
    }
    else if (discriminant > 0)
    {
        *root_1 = (-b - sqrt(discriminant)) / (2 * a);
        *root_2 = (-b + sqrt(discriminant)) / (2 * a);
        return 2;
    }
    else
        return UNKNOWN_ERROR;
}


int solve_equation(double a, double b, double c, double* root_1, double* root_2)
{
    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));
    assert(root_1 != NULL);
    assert(root_2 != NULL);

    int number_of_roots = 0;
    if (is_equal(a, (double) 0))
        number_of_roots = solve_linear_equation(b, c, root_1);
    else
        number_of_roots = solve_square_equation(a, b, c, root_1, root_2);
    return number_of_roots;
}


int is_equal(double a, double b)
{
    assert(!isinf(a));
    assert(!isinf(b));

    return fabs(a - b) < DBL_EPSILON;
}
