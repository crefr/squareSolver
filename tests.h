#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include "consts.h"

struct test_t
{
    int num;
    coeffs_t coef;
    roots_t root;
};

int runTests();
int runTest(struct test_t test);

#endif // TESTS_H_INCLUDED
