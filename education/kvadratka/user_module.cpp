#include "solving_module.h"


enum program_states {OFF, ON};


void read_koef(double* a, double* b, double* c);
void print_ans(root_number number_of_roots, double root_1, double root_2);
void clear_buffer(void);
bool check_buffer();
void ask_for_new_equations(int* state);


int main()
{
    double a_koef = 0, b_koef = 0, c_koef = 0;
    int program_state = ON;

    printf("\033[1m+++ Square Equation Solver +++\033[0m\n\n");

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
