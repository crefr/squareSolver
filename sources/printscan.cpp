#include <stdio.h>
#include <ctype.h>

#include "printscan.h"
#include "consts.h"
#include "colPrintf.h"
#include "colors.h"
#include "myassert.h"

int scanCoefs(struct coeffs_t *sq)
{
    MYASSERT(sq != NULL);
    double *ptrs[] = {&(sq -> a), &(sq -> b), &(sq -> c)};  // Указатели на коэффициенты
    int ch = EOF;

    bool flag = false;
    do
    {
        flag = false;
        int count = 0;
        for (unsigned int i = 0; i < sizeof(ptrs) / sizeof(double *); i++){
            count += scanf("%lg", ptrs[i]);
            if (!isspace(ch = getchar()) && ch != EOF)
            {
                flag = true;
                while((ch = getchar()) != '\n' && ch != EOF);
                break;
            }
        }

        if (count != 3)
            flag = true;

        while(ch != '\n' && ch != EOF && !flag)
        {
            if (!isspace(ch))
            {
                flag = true;
                while((ch = getchar()) != '\n' && ch != EOF);
                break;
            }
            ch = getchar();
        }

        if (flag)
        {
            if (ch == EOF)
                return 0;
            else
                printf("Try again\n");
        }

    } while(flag);

    return 1;
}

void printRoots(struct roots_t root){
    switch(root.nRoots)
    {
        case 0:
            colPrintf(RED, "No real roots");
            break;

        case 1:
            colPrintf(GREEN, "x = %lg\n", root.x1);
            break;

        case 2:
            colPrintf(GREEN, "x1 = %lg\nx2 = %lg\n", root.x1, root.x2);
            break;

        case INF_ROOTS:
            colPrintf(GREEN, "Infinite roots\n");
            break;

        default:
            colPrintf(GREEN, "ERROR nRoots = %d\n", root.nRoots);
            break;
    }
}
