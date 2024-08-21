#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED
struct test_t tests[] =
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
#endif // TESTS_H_INCLUDED
