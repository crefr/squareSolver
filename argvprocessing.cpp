#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "argvprocessing.h"
#include "tests.h"
#include "myassert.h"
#include "colPrintf.h"

// const int ERROR_ = -10;
// const int EXIT_ = -20;
// enum EXITS {BAD, GOOD};

// const int MAXLINE = 100;

enum valtypes {V_NOTDEF = 0, V_BOOL, V_STRING, V_DOUBLE, V_INT};
enum flags {H = 0, HELP, M, C, F};
static const struct argvEx_t args[] =
{
    {.valtype = V_NOTDEF,       .fname = "-h",          .help = "standard --help"},
    {.valtype = V_NOTDEF,       .fname = "--help",      .help = "standard --help"},
    {.valtype = V_BOOL,         .fname = "-m",          .help = "switches mode to 0 or 1 (-m 0 and -m 1)"},
    {.valtype = V_BOOL,         .fname = "-c",          .help = "switches color mode to 0 or 1 (-c 0 and -c 1)"},
    {.valtype = V_STRING,       .fname = "-f",          .help = "an argument after -f will be the name of file with tests (ex. -f tests.txt) (tests.txt on default)"}
};
static const int ARGVNUM = sizeof(args) / sizeof(argvEx_t);

int argvReceive(int argc, char **argv, union fvals *fval)
{
    MYASSERT(argv != NULL);
    MYASSERT(fval != NULL);

    for(int i = 1; i < argc; i++)
    {
        int j = 0;
        for (; j < ARGVNUM; j++){
            if (strcmp(argv[i], args[j].fname) == 0){
                if (args[j].valtype == V_NOTDEF)
                    fval[j].bl = 1;
                else{
                    i++;
                    if (i >= argc)
                        return BAD;
                    if (args[j].valtype == V_BOOL)
                    {
                        if (strcmp("0", argv[i]) == 0)
                            fval[j].bl = 0;
                        else if (strcmp("1", argv[i]) == 0)
                            fval[j].bl = 1;
                        else return BAD;
                    }
                    else if (args[j].valtype == V_STRING)
                        strcpy(fval[j].str, argv[i]);
                    else return BAD;
                }
                break;
            }
        } if(j == ARGVNUM) return BAD;
    }
    return GOOD;
}

int argvHandler(union fvals *fval)
{
    MYASSERT(fval != NULL);

    setColFlag(fval[C].bl);
    if (fval[H].bl || fval[HELP].bl)
    {
        printf("############################################################################\n");
        for (int flagi = 0; flagi < ARGVNUM; flagi++)
            printf("%10s\t%s\n", args[flagi].fname, args[flagi].help);
        printf("############################################################################\n");
        return EXIT_;
    }
    if (fval[M].bl)
    {
        if (!frunTests(fval[F].str))
        {
            colPrintf(RED, "TESTING FAILED\n");
            return ERROR_;
        }
        return EXIT_;
    }
    return 0;
}

void setFlags(union fvals *fval)
{
    fval[H].bl = 0;
    fval[HELP].bl = 0;
    fval[M].bl = 0;
    fval[C].bl = 1;
    strcpy(fval[F].str, "tests.txt");
}
