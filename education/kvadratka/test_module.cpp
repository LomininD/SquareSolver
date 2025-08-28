//#include <stdlib.h>
#include "test_module.h"


#define ROOT_1_REF data -> correct_root_1
#define ROOT_2_REF data -> correct_root_2
#define NUMBER_OF_ROOTS_REF data -> correct_number_of_roots


static void test_solve_equation(test_data* tests, int number_of_tests);
static int test(test_data* data);
static root_number str_to_root_number(char str[]);
static void read_tests(FILE* fp, int number_of_tests, test_data* tests);


void run_tests(void)
{
    printf("(unit test mode)\n");

    FILE *fp = fopen("tests.txt", "r");
    int number_of_tests = 0;
    fscanf(fp, "%d\n", &number_of_tests);
    test_data* tests = (test_data*) calloc((size_t)number_of_tests, sizeof(test_data));

    read_tests(fp, number_of_tests, tests);

    test_solve_equation(tests, number_of_tests);

    free(tests);
    fclose(fp);
}


static void read_tests(FILE* fp, int number_of_tests, test_data* tests)
{
    assert(fp != NULL);
    assert(tests != NULL);

    for (int i = 0; i < number_of_tests; ++i)
    {
        double a = 0, b = 0, c = 0;
        double correct_root_1 = 0, correct_root_2 = 0;
        char roots_str[10] = "";

        fscanf(fp, "a = %lg, b = %lg, c = %lg, correct_number_of_roots = %[^,], "
                   "correct_root_1 = %lg, correct_root_2 = %lg\n", &a, &b, &c,
                   roots_str, &correct_root_1, &correct_root_2);

        root_number correct_number_of_roots = str_to_root_number(roots_str);

        test_data test = {a, b, c, correct_number_of_roots, correct_root_1, correct_root_2};

        tests[i] = test;
    }
}


static root_number str_to_root_number(char str[])
{
    if (!strcmp(str, "NO_ROOTS"))
        return NO_ROOTS;
    else if (!strcmp(str, "ONE_ROOT"))
        return ONE_ROOT;
    else if (!strcmp(str, "TWO_ROOTS"))
        return TWO_ROOTS;
    else // if (strcmp(str, "INF_ROOTS")):
        return INF_ROOTS;
}


static void test_solve_equation(test_data* tests, int number_of_tests)
{
    assert(tests != NULL);

    int succeeded = 0;

    for (int i = 0; i < number_of_tests; ++i)
        succeeded += test(&tests[i]);

    printf(MAKE_BOLD("Passed %d/%d\n"), succeeded, number_of_tests);
}


static int test(test_data* data)
{
    assert(data != NULL);
    assert(isfinite(A_KOEF));
    assert(isfinite(B_KOEF));
    assert(isfinite(C_KOEF));
    assert(isfinite(ROOT_1_REF));
    assert(isfinite(ROOT_2_REF));

    double root_1 = 0, root_2 = 0;

    quadratic_equation_data data_square = {A_KOEF, B_KOEF, C_KOEF, root_1, root_2};

    root_number number_of_roots = solve_equation(&data_square);

    if (!(number_of_roots == NUMBER_OF_ROOTS_REF
       && is_equal(data_square.root_1, ROOT_1_REF)
       && is_equal(data_square.root_2, ROOT_2_REF))
       )
    {
        printf(MAKE_BOLD_RED("FAILED") ": "
        "solve_equation({%lg, %lg, %lg, x1, x2}) --> "
        "roots: %d, x1 = %lg, x2 = %lg \n"
        "(should be roots: %d, x1 = %lg, x2 = %lg)\n", A_KOEF, B_KOEF, C_KOEF,
        number_of_roots, data_square.root_1, data_square.root_2,
        NUMBER_OF_ROOTS_REF, ROOT_1_REF, ROOT_2_REF);
        return 0;
    }
    else
    {
        printf(MAKE_BOLD_GREEN("OK\n"));
        return 1;
    }
}
