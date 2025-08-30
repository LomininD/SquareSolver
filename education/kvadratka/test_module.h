#ifndef TEST_MODULE_H
#define TEST_MODULE_H


#include "font_styles.h"
#include "solving_module.h"
#include <string.h>


struct test_data
{
    double a;
    double b;
    double c;
    root_number correct_number_of_roots;
    double correct_root_1;
    double correct_root_2;
};

void run_tests(const char * test_file);

#endif
