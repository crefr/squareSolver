#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "../headers/argvprocessing.h"
#include "myassert.h"


//enum flags {H = 0, HELP, M, C, F};
// static const struct argvEx_t args[] =
// {
//     {.valtype = V_NOTDEF,       .fname = "-h",          .help = "standard --help"},
//     {.valtype = V_NOTDEF,       .fname = "--help",      .help = "standard --help"},
//     {.valtype = V_BOOL,         .fname = "-m",          .help = "switches mode to 0 or 1 (-m 0 and -m 1)"},
//     {.valtype = V_BOOL,         .fname = "-c",          .help = "switches color mode to 0 or 1 (-c 0 and -c 1)"},
//     {.valtype = V_STRING,       .fname = "-f",          .help = "an argument after -f will be the name of file with tests (ex. -f tests.txt) (tests.txt on default)"}
// };
// static const int ARGVNUM = sizeof(args) / sizeof(argvEx_t);

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
