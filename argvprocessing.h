#ifndef ARGVPR_INCLUDED
#define ARGVPR_INCLUDED

const int MAXLIN = 100;

struct argvEx_t
{
    unsigned int valtype;
    char fname[MAXLIN];
    //unsigned int fval : 1;s
    const char *help;
};

union fvals
{
    unsigned int bl : 1;
    int in;
    double dbl;
    char str[MAXLIN];
};

int argvReceive(int argc, char **argv, union fvals *fval);
int argvHandler(union fvals *fval);
void setFlags(union fvals *fval);


#endif
