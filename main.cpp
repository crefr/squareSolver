#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include "colors.h"
#include "printscan.h"
#include "sqmath.h"
#include "consts.h"
#include "tests.h"
#include "colPrintf.h"
#include "myassert.h"
#include "argvprocessing.h"

int main(int argc, char *argv[])
{
    MYASSERT(argv != NULL);

    union fvals fval[5];

    setFlags(fval);
    if (argvReceive(argc, argv, fval) == BAD)
    {
        colPrintf(RED, "CMD args ERROR\n");
        return ERROR_;
    }

    int hh = argvHandler(fval);
    if(hh == EXIT_)
        return 0;
    else if (hh == ERROR_)
        return ERROR_;

    struct coeffs_t sq;
    struct roots_t root;

    printf("# SquareSolver\n"
           "# Made for Summer school MIPT\n");

    printf("Enter a, b, c coefficients (only one number in each line): \n");
    if (scanCoefs(&sq) == 0)
    {
        colPrintf(RED, "!!!INPUT ERROR!!!\n");
        return ERROR_;
    }
    sqSolve(sq, &root);
    printRoots(root);
    return 0;
}
