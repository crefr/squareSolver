#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "../headers/argvprocessing.h"
#include "myassert.h"

int argvReceive(const int argc, char **argv, union fvals *fval)
{
    MYASSERT(argv != NULL);
    MYASSERT(fval != NULL);

    int argindex = 1;
    while(argindex < argc)
    {
        int flagindex = 0;
        for (; flagindex < ARGVNUM; flagindex++){
            if (strcmp(argv[argindex], args[flagindex].fname) == 0){
                if (args[flagindex].valtype == V_NOTDEF)
                    fval[flagindex].bl = 1;
                else{
                    argindex++;
                    if (argindex >= argc)
                        return BAD;
                    if(fillFval(argv, argindex, fval, flagindex) == BAD)
                        return BAD;
                }
                break;
            }
        } if(flagindex == ARGVNUM) return BAD;
        argindex++;
    }
    return GOOD;
}


int fillFval(char **argv, const int argindex, union fvals *fval, const int flagindex)
{
    MYASSERT(argv != NULL);
    MYASSERT(fval != NULL);
    switch(args[flagindex].valtype)
    {
        case V_BOOL:
            if (strcmp("0", argv[argindex]) == 0)
                fval[flagindex].bl = 0;
            else if (strcmp("1", argv[argindex]) == 0)
                fval[flagindex].bl = 1;
            else return BAD;
            break;
        case V_STRING:
            strcpy(fval[flagindex].str, argv[argindex]);
            break;
        case V_DOUBLE:
            if (sscanf(argv[argindex], "%lg", &(fval[flagindex].dbl)) != 1)
                return BAD;
            break;
        case V_INT:
            if (sscanf(argv[argindex], "%d", &(fval[flagindex].in)) != 1)
                return BAD;
            break;
        default:
            return BAD;
            break;
    }
    return GOOD;
}


void printHelp()
{
    printf("############################################################################\n");
    for (int flagi = 0; flagi < ARGVNUM; flagi++)
        printf("%10s\t%s\n", args[flagi].fname, args[flagi].help);
    printf("############################################################################\n");
}

void setFlags(union fvals *fval)
{
    fval[H].bl = 0;
    fval[HELP].bl = 0;
    fval[M].bl = 0;
    fval[C].bl = 1;
    strcpy(fval[F].str, "tests.txt");
}
