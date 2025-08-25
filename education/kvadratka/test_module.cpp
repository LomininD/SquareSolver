#include "font_styles.h"
#include "solving_module.h"


#define ROOT_1_REF data -> correct_root_1
#define ROOT_2_REF data -> correct_root_2
#define NUMBER_OF_ROOTS_REF data -> correct_number_of_roots


struct test_data
{
    const double a;
    const double b;
    const double c;
    root_number correct_number_of_roots;
    double correct_root_1;
    double correct_root_2;
};


const test_data tests[] = {
    {1, 2, 1, ONE_ROOT, -1, 0},
    {0, 0, 1, NO_ROOTS, 0, 0},
    {1, -5, 6, TWO_ROOTS, 2, 3},
    {0, 1, 2, ONE_ROOT, -2, 0},
    {0, 0, 0, INF_ROOTS, 0, 0},
    {1, 0, 0, ONE_ROOT, 0, 0},
    {5, 0, 0, ONE_ROOT, 0, 0},
    {0, 1, 0, ONE_ROOT, 0, 0},
    {1, 1, 0, TWO_ROOTS, -1, 0},
    {-1, 0, 0, ONE_ROOT, 0, 0}
};


void test_solve_equation(void);
int test(const test_data* data);


int main()
{
    printf (BOLD "+++ Square Equation Solver +++\n" RESET_FONT);
    printf("(unit test mode)\n");
    test_solve_equation();

    return 0;
}


int test(const test_data* data)
{
    assert(data != NULL);


    assert(isfinite(A_KOEF));
    assert(isfinite(B_KOEF));
    assert(isfinite(C_KOEF));
    assert(isfinite(ROOT_1_REF));
    assert(isfinite(ROOT_2_REF));

    double root_1 = 0, root_2 = 0;

    square_equation_data data_square = {A_KOEF, B_KOEF, C_KOEF, root_1, root_2};

    root_number number_of_roots = solve_equation(&data_square);

    if (!(number_of_roots == NUMBER_OF_ROOTS_REF
       && is_equal(data_square.root_1, ROOT_1_REF)
       && is_equal(data_square.root_2, ROOT_2_REF))
       )
    {
        printf(BOLD_RED "FAILED" RESET_FONT ": "
        "solve_equation({%lg, %lg, %lg, x1, x2}) --> "
        "roots: %d, x1 = %lg, x2 = %lg \n"
        "(should be roots: %d, x1 = %lg, x2 = %lg)\n", A_KOEF, B_KOEF, C_KOEF,
        number_of_roots, data_square.root_1, data_square.root_2,
        NUMBER_OF_ROOTS_REF, ROOT_1_REF, ROOT_2_REF);
        return 0;
    }
    else
    {
        printf(BOLD_GREEN "OK\n" RESET_FONT);
        return 1;
    }
}


void test_solve_equation(void)
{
    int succeeded = 0, max_succeeded = 0;

    size_t size = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < size; ++i)
    {
        succeeded += test(&tests[i]);
        max_succeeded += 1;
    }

    printf(BOLD "Passed %d/%d\n" RESET_FONT, succeeded, max_succeeded);
}
