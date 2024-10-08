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
#include "argvprocessing.h"

//! @brief Действует в зависимости от значений флагов в fval
//! @param      [IN]    fval    массив типа union fvals со значениями флагов
//! @return     Может вернуть EXIT (выйти из программы), BAD (ошибка) и GOOD (все хорошо)
int argvHandler(const union fvals *fval);

int main(int argc, char *argv[])
{
    union fvals fval[ARGVNUM];
    setFlags(fval); //обнуляет флаги
    if (argvReceive(argc, argv, fval) == BAD)
    {
        colPrintf(RED, "CMD args ERROR\n");
        return ERROR_;
    }

    int handlerOut = argvHandler(fval);
    if(handlerOut == EXIT)
        return 0;
    else if (handlerOut == BAD)
        return ERROR_;

    struct coeffs_t sq;
    struct roots_t root;

    printf("# SquareSolver\n"
           "# Made for Summer school MIPT\n");

    printf("Enter a, b, c coefficients (separate them with spaces or enters): \n");
    if (scanCoefs(&sq) == 0)
    {
        colPrintf(RED, "!!!INPUT ERROR!!!\n");
        return ERROR_;
    }
    sqSolve(sq, &root);
    printRoots(root);
    return 0;
}

int argvHandler(const union fvals *fval)
{
    MYASSERT(fval != NULL);

    setColFlag(fval[C].bl);
    if (fval[H].bl || fval[HELP].bl)
    {
        printHelp();
        return EXIT;
    }
    if (fval[M].bl)
    {
        if (!frunTests(fval[F].str))
        {
            return BAD;
        }
        return EXIT;
    }
    return GOOD;
}
