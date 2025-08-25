#include "solving_module.h"
#include "font_styles.h"


enum program_states {OFF, ON};


void read_koef(double koefs[]); // do I need const here?
void print_ans(root_number number_of_roots, square_equation_data data);
void clear_buffer(void);
bool check_buffer();
program_states ask_for_new_equations(void);


int main()
{
    double koefs[3] = {};

    int program_state = ON;

    printf(BOLD "+++ Square Equation Solver +++\n\n" RESET_FONT);

    while (program_state == ON)
    {
        read_koef(koefs);

        double root_1 = 0, root_2 = 0;
        square_equation_data data = {koefs[0], koefs[1], koefs[2], root_1, root_2};

        root_number number_of_roots = solve_equation(&data);

        print_ans(number_of_roots, data);

        program_state = ask_for_new_equations();
    }
    return 0;
}


program_states ask_for_new_equations(void)
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


void clear_buffer(void)
{
    int c = '\0';
    while ((c = getchar()) != '\n' && c != EOF);
}


bool check_buffer()
{
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n')
        if (c != ' ' && c != '\n' && c != '\t')
            return false;
    return true;
}


void read_koef(double koefs[])
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


void print_ans(root_number number_of_roots, square_equation_data data)
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
