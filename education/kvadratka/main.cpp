#include "test_module.h"
#include "user_module.h"


// TODO: add asserts


static void print_incorrect_flag_message(void);
static void determine_mode(int argc, char* argv[]);


int main(int argc, char* argv[])
{
    //printf(MAKE_BOLD_RED ("MEOW\n"));

    printf(MAKE_BOLD("+++ Square Equation Solver +++\n"));
    printf("(c) Dmitry Lominin, 2025\n\n");

    determine_mode(argc, argv);

    //printf(MAKE_BOLD_RED("COMMIT GITHUB!!!\n"));

    return 0;
}


static void determine_mode(int argc, char* argv[])
{
    switch (argc)
    {
        case 1:
            run_user_interface(); // TODO: --help
            break;
        default:
            if (!strcmp(argv[1], "-test"))
                run_tests();
            else if (!strcmp(argv[1], "-user"))
                run_user_interface();
            else
                print_incorrect_flag_message();
            break;
    }
}


static void print_incorrect_flag_message(void)
{
    printf("Incorrect command line argument\n");
}
