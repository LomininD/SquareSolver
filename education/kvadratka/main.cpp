#include "test_module.h"
#include "user_module.h"


static void print_help(void);
static void determine_mode(int argc, char* argv[]);


int main(int argc, char* argv[])
{
    //printf(MAKE_BOLD_RED ("MEOW\n"));

    printf(MAKE_BOLD("+++ Quadratic Equation Solver +++\n"));
    printf("(c) Dmitry Lominin, 2025\n\n");

    determine_mode(argc, argv);

    //printf(MAKE_BOLD_RED("COMMIT GITHUB!!!\n"));

    return 0;
    
}


static void determine_mode(int argc, char* argv[])
{
    assert(argv != NULL);

    switch (argc)
    {
        case 1:
            print_help();
            break;
        default:
            if (!strcmp(argv[1], "-test"))
            {
                run_tests();
            }
            else if (!strcmp(argv[1], "-user"))
            {
                run_user_interface();
            }
            else if (!strcmp(argv[1], "-all"))
            {
                run_tests();
                run_user_interface();
            }
            else if (!strcmp(argv[1], "--help"))
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
    printf(MAKE_BOLD("Possible launch flags:\n") "-user to launch program in user mode\n"
           "-test to launch program in unit test mode\n"
           "-all to launch program in both modes\n"
           "--help to get info about launch flags\n");

}
