#include "user_module.h"


enum program_states {OFF, ON};


static void read_koef(double* const koefs);
static void print_ans(root_number number_of_roots, square_equation_data data);
static void clear_buffer(void);
static bool check_buffer();
static program_states ask_for_new_equations(void);


void run_user_inteface(void)
{
    double koefs[3] = {};

    int program_state = ON;

    while (program_state == ON)
    {
        read_koef(koefs);

        double root_1 = 0, root_2 = 0;
        square_equation_data data = {koefs[0], koefs[1], koefs[2], root_1, root_2};

        root_number number_of_roots = solve_equation(&data);

        print_ans(number_of_roots, data);

        program_state = ask_for_new_equations();
    }
}


static program_states ask_for_new_equations(void)
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
    {
        return ON;
    }
    else
    {
        printf("I\'ll be back...\n");
        return OFF;
    }
}


static void clear_buffer(void)
{
    int c = '\0';
    while ((c = getchar()) != '\n' && c != EOF);
}


static bool check_buffer()
{
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n')
        if (c != ' ' && c != '\n' && c != '\t')
            return false;
    return true;
}


static void read_koef(double* const koefs)
{
    assert(koefs != NULL);

    printf("Enter a, b, c parameters for equation ax^2 + bx + c = 0:\n");

    int correct_koef_number = scanf("%lg %lg %lg", &koefs[0], &koefs[1], &koefs[2]);
    while (correct_koef_number != 3 || !check_buffer())
    {
        printf("Wrong input. Please try again:\n");
        clear_buffer();
        correct_koef_number = scanf("%lg %lg %lg", &koefs[0], &koefs[1], &koefs[2]);
    }
}


static void print_ans(root_number number_of_roots, square_equation_data data)
{
    assert(isfinite(data.root_1));
    assert(isfinite(data.root_2));

    switch (number_of_roots)
    {
        case NO_ROOTS:
            printf("This equation does not have any roots\n");
            break;
        case ONE_ROOT:
            printf("This equation has 1 root:\n");
            printf("x = %lg\n", data.root_1);
            break;
        case TWO_ROOTS:
            printf("This equation has 2 roots:\n");
            printf("x1 = %lg, x2 = %lg\n", data.root_1, data.root_2);
            break;
        case INF_ROOTS:
            printf("This equation has infinite number of roots\n");
            break;
        default:
            printf("Unexpected error");
            break;
    }
}
