#include "solving_module.h"


void test_solve_equation(void);
void test(double a, double b, double c, root_number correct_number_of_roots,
          double correct_root_1, double correct_root_2, int* succeeded, int* max_succeeded);


int main()
{
    printf ("\033[1m+++ Square Equation Solver +++\033[0m\n");
    printf("(unit test mode)\n");
    test_solve_equation();

    return 0;
}


void test(double a, double b, double c, root_number correct_number_of_roots,
          double correct_root_1, double correct_root_2, int* succeeded, int* max_succeeded)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(correct_root_1));
    assert(isfinite(correct_root_2));

    double root_1 = 0, root_2 = 0;

    *max_succeeded += 1;

    root_number number_of_roots = solve_equation(a, b, c, &root_1, &root_2);
    if (!(number_of_roots == correct_number_of_roots
       && is_equal(root_1, correct_root_1)
       && is_equal(root_2, correct_root_2))
       )
    {
        printf("\033[1;31mFAILED\033[0m: "
        "solve_equation(%lg, %lg, %lg, &x1, &x2) --> "
        "roots: %d, x1 = %lg, x2 = %lg \n"
        "(should be roots: %d, x1 = %lg, x2 = %lg)\n", a, b, c, number_of_roots, root_1,
        root_2, correct_number_of_roots, correct_root_1, correct_root_2);
    }
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
    test(0, 0, 0, INF_ROOTS, 0, 0, &succeeded ,&max_succeeded);
    test(1, 0, 0, ONE_ROOT, 0, 0, &succeeded ,&max_succeeded);
    test(5, 0, 0, ONE_ROOT, 0, 0, &succeeded ,&max_succeeded);
    test(0, 1, 0, ONE_ROOT, 0, 0, &succeeded ,&max_succeeded);
    test(1, 1, 0, TWO_ROOTS, -1, 0, &succeeded ,&max_succeeded);

    printf("\033[1mPassed %d/%d\033[0m\n", succeeded, max_succeeded);
}
