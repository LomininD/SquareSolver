#include "test_module.h"
#include "user_module.h"



int main()
{
    //printf(MAKE_BOLD_RED ("MEOW\n"));
    
    printf(MAKE_BOLD("+++ Square Equation Solver +++\n"));
    printf("(c) Dmitry Lominin, 2025\n\n");

    run_tests();

    //run_user_inteface();

    //printf(MAKE_BOLD_RED("COMMIT GITHUB!!!\n"));

    return 0;
}

