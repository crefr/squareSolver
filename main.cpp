#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

const int INF_ROOTS = -1;
const double EPSILON = 0.00001;

int sqSolve(double a, double b, double c, double *x1, double *x2);

int main()
{
    printf("# SquareSolver\n"
           "# Made for Summer school MIPT\n");

    printf("Enter a, b, c coefficients:\n");

    double a = 0, b = 0, c = 0;
    while(scanf("%lg %lg %lg", &a, &b, &c) != 3)  {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Try again\n");
    }

    double x1 = 0, x2 = 0;
    int nRoots = sqSolve(a, b, c, &x1, &x2);

    switch(nRoots)
    {
        case 0:
            printf("No real roots");
            break;

        case 1:
            printf("x = %lg\n", x1);
            break;

        case 2:
            printf("x1 = %lg\nx2 = %lg\n", x1, x2);
            break;

        case INF_ROOTS:
            printf("Infinite roots\n");
            break;

        default:
            printf("ERROR nRoots = %d\n", nRoots);
            return 1;
            break;
    }
    return 0;
}


//! @brief sqSolve - function that solves square equations and returns real roots
//!
//! @param   [in]     a     coefficient a
//! @param   [in]     b     coefficient b
//! @param   [in]     c     coefficient c
//! @param   [out]    x1    pointer to first root
//! @param   [out]    x2    pointer to second root
//!
//! @return number of real roots for the equation
//! @note In case of infinite roots returns INF_ROOTS

int sqSolve(double a, double b, double c, double *x1, double *x2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);


    if (fabs(a) < EPSILON)
    {
        if (fabs(b) < EPSILON)
            return (fabs(c) < EPSILON) ? INF_ROOTS : 0;
        *x1 = -c/b;
        return 1;
    }

    double D = b*b - 4*a*c;
    if (fabs(D) < EPSILON)
    {
        *x1 = -b/(2*a);
        return 1;
    }
    else if (D > 0)
    {
        double sqrt_D = sqrt(D);
        *x1 = (-b+sqrt_D)/(2*a);
        *x2 = (-b-sqrt_D)/(2*a);
        return 2;
    }
    else
        return 0;
}

