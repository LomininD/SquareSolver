#include "font_styles.h"
#include "solving_module.h"


void test_solve_equation(void);
int test(double a, double b, double c, root_number correct_number_of_roots,
          double correct_root_1, double correct_root_2);


int main()
{
    printf (BOLD "+++ Square Equation Solver +++\n" RESET_FONT);
    printf("(unit test mode)\n");
    test_solve_equation();

    return 0;
}


int test(double a, double b, double c, root_number correct_number_of_roots,
          double correct_root_1, double correct_root_2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(correct_root_1));
    assert(isfinite(correct_root_2));

    double root_1 = 0, root_2 = 0;

    root_number number_of_roots = solve_equation(a, b, c, &root_1, &root_2);
    if (!(number_of_roots == correct_number_of_roots
       && is_equal(root_1, correct_root_1)
       && is_equal(root_2, correct_root_2))
       )
    {
        printf(BOLD_RED "FAILED" RESET_FONT ": "
        "solve_equation(%lg, %lg, %lg, &x1, &x2) --> "
        "roots: %d, x1 = %lg, x2 = %lg \n"
        "(should be roots: %d, x1 = %lg, x2 = %lg)\n", a, b, c, number_of_roots, root_1,
        root_2, correct_number_of_roots, correct_root_1, correct_root_2);
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
    int succeeded = 0, max_succeeded = 9;

    succeeded += test(1, 2, 1, ONE_ROOT, -1, 0);
    succeeded += test(0, 0, 1, NO_ROOTS, 0, 0);
    succeeded += test(1, -5, 6, TWO_ROOTS, 2, 3);
    succeeded += test(0, 1, 2, ONE_ROOT, -2, 0);
    succeeded += test(0, 0, 0, INF_ROOTS, 0, 0);
    succeeded += test(1, 0, 0, ONE_ROOT, 0, 0);
    succeeded += test(5, 0, 0, ONE_ROOT, 0, 0);
    succeeded += test(0, 1, 0, ONE_ROOT, 0, 0);
    succeeded += test(1, 1, 0, TWO_ROOTS, -1, 0);

    printf(BOLD "Passed %d/%d\n" RESET_FONT, succeeded, max_succeeded);
}
