//! @file


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include "colors.h"
#include "printscan.h"
#include "sqmath.h"
#include "consts.h"
#include "tests.h"
#include "colPrintf.h"

int argvReceive(int argc, char **argv, argvEx_t *args, const int argvnum);

int main(int argc, char *argv[])
{
    struct argvEx_t args[] =
    {
        {.haveVal = 0,  .fname = "-h",       .fval = 0,    .help = "standard --help"},
        {.haveVal = 0,  .fname = "--help",   .fval = 0,    .help = "standard --help"},
        {.haveVal = 1,  .fname = "-m",       .fval = 0,    .help = "switches mode to 0 or 1 (-m 0 and -m 1)"},
        {.haveVal = 1,  .fname = "-c",       .fval = 1,    .help = "switches color mode to 0 or 1 (-c 0 and -c 1)"},
    };
    const int ARGVNUM = sizeof(args) / sizeof(argvEx_t);

    setColFlag(1);

    if (argvReceive(argc, argv, args, ARGVNUM) == BAD)
    {
        colPrintf(RED, "CMD args ERROR\n");
        return ERROR_;
    }

    setColFlag(args[C].fval);

    if (args[H].fval == 1 || args[HELP].fval == 1)
    {
        printf("############################################################################\n");
        for (int flagi = 0; flagi < ARGVNUM; flagi++)
            printf("%10s\t%s\n", args[flagi].fname, args[flagi].help);
        printf("############################################################################\n");
        return 0;
    }

    if (args[M].fval == 1)
    {
        if (!runTests())
        {
            colPrintf(RED, "TESTING FAILED\n");
            return ERROR_;
        }
        return 0;
    }
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

int argvReceive(int argc, char **argv, argvEx_t *args, const int argvnum)
{
    for(int i = 1; i < argc; i++)
    {
        int j;
        for (j = 0; j < argvnum; j++)
        {
            if (strcmp(argv[i], args[j].fname) == 0)
            {
                if (args[j].haveVal == 0)
                    args[j].fval = 1;
                else
                {
                    i++;
                    if (i >= argc)
                        return BAD;
                    if (strcmp(argv[i], "0") == 0)
                        args[j].fval = 0;
                    else if (strcmp(argv[i], "1") == 0)
                        args[j].fval = 1;
                    else
                        return BAD;
                }
                break;
            }
        } if(j == argvnum) return BAD;
    }
    return GOOD;
}
/*
добавить в структуру argsvEx_t поле с описанием тега для --help
переделать colPrintf (сделать с флагом c) в аргументах
переделать argvReceive
раздельная компиляция (хотя бы в раздельных файлах)
*/
