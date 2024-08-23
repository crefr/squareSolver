//! @file

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

int argvReceive(int argc, char **argv, const struct argvEx_t *argvs, unsigned int *fval, const int argvnum);
int argvHandler(unsigned int *fval);

enum flags {H = 0, HELP, M, C};
static const struct argvEx_t args[] =
{
    {.haveVal = 0,  .fname = "-h",      .help = "standard --help"},
    {.haveVal = 0,  .fname = "--help",  .help = "standard --help"},
    {.haveVal = 1,  .fname = "-m",      .help = "switches mode to 0 or 1 (-m 0 and -m 1)"},
    {.haveVal = 1,  .fname = "-c",      .help = "switches color mode to 0 or 1 (-c 0 and -c 1)"},
};
static const int ARGVNUM = sizeof(args) / sizeof(argvEx_t);

int main(int argc, char *argv[])
{
    MYASSERT(argv != NULL);
    unsigned int fval[ARGVNUM] = {0, 0, 0, 1};
    setColFlag(fval[C]);
    if (argvReceive(argc, argv, args, fval, ARGVNUM) == BAD)
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
        //printf((args[C].fval) ? RED "!!!INPUT ERROR!!!" : "!!!INPUT ERROR!!!");
        return ERROR_;
    }
    sqSolve(sq, &root);
    printRoots(root);
    return 0;
}

int argvReceive(int argc, char **argv, const struct argvEx_t *argvs, unsigned int *fval, const int argvnum)
{
    MYASSERT(argv != NULL);
    MYASSERT(argvs != NULL);
    MYASSERT(fval != NULL);

    for(int i = 1; i < argc; i++)
    {
        int j;
        for (j = 0; j < argvnum; j++)
        {
            if (strcmp(argv[i], argvs[j].fname) == 0)
            {
                if (argvs[j].haveVal == 0)
                    fval[j] = 1;
                else
                {
                    i++;
                    if (i >= argc)
                        return BAD;
                    if (strcmp(argv[i], "0") == 0)
                        fval[j] = 0;
                    else if (strcmp(argv[i], "1") == 0)
                        fval[j] = 1;
                    else
                        return BAD;
                }
                break;
            }
        } if(j == argvnum) return BAD;
    }
    return GOOD;
}

int argvHandler(unsigned int *fval)
{
    MYASSERT(fval != NULL);

    setColFlag(fval[C]);
    if (fval[H] == 1 || fval[HELP] == 1)
    {
        printf("############################################################################\n");
        for (int flagi = 0; flagi < ARGVNUM; flagi++)
            printf("%10s\t%s\n", args[flagi].fname, args[flagi].help);
        printf("############################################################################\n");
        return EXIT_;
    }
    if (fval[M])
    {
        if (!frunTests("tests.txt"))
        {
            colPrintf(RED, "TESTING FAILED\n");
            return ERROR_;
        }
        return EXIT_;
    }
    return 0;
}
