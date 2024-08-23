#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "tests.h"
#include "consts.h"
#include "colPrintf.h"
#include "sqmath.h"
#include "colors.h"
#include "myassert.h"


int runTest(struct test_t test)
{
    struct roots_t root;
    sqSolve(test.coef, &root);
    if (!equals(test.root.nRoots, root.nRoots) || !eqRoots(test.root, root))
    {

        colPrintf(RED, "Error Test %d:\na = %lg, b = %lg, c = %lg\n"
                       "x1 = %lg, x2 = %lg, nRoots = %d\n"
                       "Expected:\nx1 = %lg, x2 = %lg, nRoots = %d\n",
                        test.num, test.coef.a, test.coef.b, test.coef.c, root.x1, root.x2, root.nRoots,
                        test.root.x1, test.root.x2, test.root.nRoots);
        return 0;
    }
    colPrintf(GREEN, "Test %d Correct\n", test.num);
    return 1;
}

int runTests()
{
    const struct test_t tests[] =
    {
        {
        .num = 1,
        .coef = {.a = 0,.b = 0,.c = 0},
        .root = {.x1 = 0,.x2 = 0,.nRoots = INF_ROOTS}
        },
        {
        .num = 2,
        .coef = {.a = 0,.b = 0,.c = 1.5},
        .root = {.x1 = 0,.x2 = 0,.nRoots = 0}
        },
        {
        .num = 3,
        .coef = {.a = 2.5,.b = 0,.c = 0},
        .root = {.x1 = 0,.x2 = 0,.nRoots = 1}
        },
        {
        .num = 4,
        .coef = {.a = 0,.b = 5.6,.c = 0},
        .root = {.x1 = 0,.x2 = 0,.nRoots = 1}
        },
        {
        .num = 5,
        .coef = {.a = 1,.b = 2,.c = 1},
        .root = {.x1 = -1,.x2 = 0,.nRoots = 1}
        },
        {
        .num = 6,
        .coef = {.a = 0.1,.b = 0.2,.c = 0.1},
        .root = {.x1 = -1,.x2 = 0,.nRoots = 1}
        },
        {
        .num = 7,
        .coef = {.a = 1,.b = 5,.c = 6},
        .root = {.x1 = -2,.x2 = -3,.nRoots = 2}
        },
        {
        .num = 8,
        .coef = {.a = 1,.b = 0,.c = 5.5},
        .root = {.x1 = 0,.x2 = 0,.nRoots = 0}
        },
        {
        .num = 9,
        .coef = {.a = 0,.b = 2.5,.c = -5.5},
        .root = {.x1 = 5.5/2.5,.x2 = 0,.nRoots = 1}
        },
        {
        .num = 10,
        .coef = {.a = 1,.b = -4,.c = 3},
        .root = {.x1 = 3,.x2 = 1,.nRoots = 2}
        },
        {
        .num = 11,
        .coef = {.a = 1,.b = -4,.c = 0},
        .root = {.x1 = 4,.x2 = 0,.nRoots = 2}
        },
        {
        .num = 12,
        .coef = {.a = 1,.b = -4,.c = 0},
        .root = {.x1 = 0,.x2 = 4,.nRoots = 2}
        }
    };

    const int TESTNUM = sizeof(tests) / sizeof(test_t);

    for (int i = 0; i < TESTNUM; i++)
    {
        if (runTest(tests[i]) == 0)
            return 0;
    }
    return 1;
}
