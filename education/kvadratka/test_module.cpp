#include "font_styles.h"
#include "solving_module.h"


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
int test(test_data data);


int main()
{
    printf (BOLD "+++ Square Equation Solver +++\n" RESET_FONT);
    printf("(unit test mode)\n");
    test_solve_equation();

    return 0;
}


int test(test_data data)
{
    assert(isfinite(data.a));
    assert(isfinite(data.b));
    assert(isfinite(data.c));
    assert(isfinite(data.correct_root_1));
    assert(isfinite(data.correct_root_2));

    double root_1 = 0, root_2 = 0;

    square_equation_data data_square = {data.a, data.b, data.c, root_1, root_2};

    root_number number_of_roots = solve_equation(&data_square);
    if (!(number_of_roots == data.correct_number_of_roots
       && is_equal(data_square.root_1, data.correct_root_1)
       && is_equal(data_square.root_2, data.correct_root_2))
       )
    {
        printf(BOLD_RED "FAILED" RESET_FONT ": "
        "solve_equation({%lg, %lg, %lg, x1, x2}) --> "
        "roots: %d, x1 = %lg, x2 = %lg \n"
        "(should be roots: %d, x1 = %lg, x2 = %lg)\n", data.a, data.b, data.c,
        number_of_roots, data_square.root_1, data_square.root_2,
        data.correct_number_of_roots, data.correct_root_1, data.correct_root_2);
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

    for (test_data test_case : tests)
    {
        succeeded += test(test_case);
        max_succeeded += 1;
    }

    /*
    succeeded += test(1, 2, 1, ONE_ROOT, -1, 0);
    succeeded += test(0, 0, 1, NO_ROOTS, 0, 0);
    succeeded += test(1, -5, 6, TWO_ROOTS, 2, 3);
    succeeded += test(0, 1, 2, ONE_ROOT, -2, 0);
    succeeded += test(0, 0, 0, INF_ROOTS, 0, 0);
    succeeded += test(1, 0, 0, ONE_ROOT, 0, 0);
    succeeded += test(5, 0, 0, ONE_ROOT, 0, 0);
    succeeded += test(0, 1, 0, ONE_ROOT, 0, 0);
    succeeded += test(1, 1, 0, TWO_ROOTS, -1, 0);
    */

    printf(BOLD "Passed %d/%d\n" RESET_FONT, succeeded, max_succeeded);
}
