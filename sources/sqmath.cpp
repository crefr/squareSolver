#include <math.h>

#include "sqmath.h"
#include "consts.h"
#include "myassert.h"
#include "myisfinite.h"

void sqSolve(const struct coeffs_t coef, struct roots_t *root)
{
    MYASSERT(root != NULL);

    MYASSERT(myisfinite(coef.a));
    MYASSERT(myisfinite(coef.b));
    MYASSERT(myisfinite(coef.c));

    root -> x1 = 0;
    root -> x2 = 0;
    root -> nRoots = -2;

    if (isZero(coef.a))
    {
        root -> nRoots = linSolve(coef.b, coef.c, &(root -> x1));
        root -> x2 =0;
        return;
    }

    double D = discr(coef);
    if (isZero(D))
    {
        root -> x1 = -coef.b/(2*coef.a);
        root -> x2 = 0;
        root -> nRoots =  1;
        return;
    }
    if (D > 0)
    {
        double sqrt_D = sqrt(D);
        root -> x1 = (-coef.b+sqrt_D)/(2*coef.a);
        root -> x2 = (-coef.b-sqrt_D)/(2*coef.a);
        root -> nRoots = 2;
        return;
    }

    root -> nRoots = 0;
}

int isZero(const double a)
{
    MYASSERT(myisfinite(a));
    return fabs(a) < EPSILON;
}

int linSolve(const double b, const double c, double *x)
{
    MYASSERT(x != NULL);
    MYASSERT(myisfinite(b));
    MYASSERT(myisfinite(c));

    if (isZero(b))
    {
        if (isZero(c))
            return INF_ROOTS;
        return 0;
    }
    *x = -c/b;
    return 1;
}

double discr(const struct coeffs_t coef)
{
    MYASSERT(myisfinite(coef.a));
    MYASSERT(myisfinite(coef.b));
    MYASSERT(myisfinite(coef.c));

    return coef.b*coef.b - 4*coef.a*coef.c;
}

int equals(const double a, const double b)
{
    MYASSERT(myisfinite(a));
    MYASSERT(myisfinite(b));
    return (fabs(a - b) < EPSILON) ? 1: 0;
}

bool eqRoots(const struct roots_t root1, const struct roots_t root2)
{
    if(equals(root1.x1, root2.x1) && equals(root1.x2, root2.x2))
        return 1;
    if(equals(root1.x1, root2.x2) && equals(root1.x2, root2.x1))
        return 1;
    return 0;
}
