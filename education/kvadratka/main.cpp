#include "test_module.h"
#include "user_module.h"


static void print_help(void);
static void determine_mode(int argc, const char* argv[]);



int main(int argc, const char* argv[])
{
    //printf(MAKE_BOLD_RED ("MEOW\n"));

    printf(MAKE_BOLD("+++ Quadratic Equation Solver +++\n"));
    printf("(c) Dmitry Lominin, 2025\n\n");

    determine_mode(argc, argv);

    //printf(MAKE_BOLD_RED("COMMIT GITHUB!!!\n"));

    return 0;

}


static void determine_mode(int argc, const char* argv[])
{
    assert(argv != NULL);

    switch (argc)
    {
        case 1:
            print_help();
            break;
        default:
            if (strcmp(argv[1], "--test") == 0 || strcmp(argv[1], "-t") == 0)
            {
                if (argc == 3)
                {
                    run_tests(argv[2]);
                }
                else
                {
                    run_tests("tests.txt");
                }
            }
            else if (strcmp(argv[1], "--user") == 0 || strcmp(argv[1], "-u") == 0)
            {
                run_user_interface();
            }
            else if (strcmp(argv[1], "--all") == 0 || strcmp(argv[1], "-a") == 0)
            {
                run_tests("tests.txt");
                run_user_interface();
            }
            else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-help") == 0)
            {
                print_help();
            }
            else
            {
                printf("Incorrect flag. Here are the examples of the correct ones:\n");
                print_help();
            }
            break;
    }
}


static void print_help(void)
{
    printf(MAKE_BOLD("Possible launch flags:\n") "--user (-u) to launch program in user mode\n"
           "--test (-t) to launch program in unit test mode\n"
           "--all (-a) to launch program in both modes\n"
           "--help (-h) to get info about launch flags\n");

}
