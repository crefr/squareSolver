#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

const int INF_ROOTS = -1;
const double EPSILON = 0.00001;

void sqSolve(struct coeffs_t coef, struct roots_t *root);
int isZero(const double a);
void scanCoefs(struct coeffs_t *coeffs);
void printRoots(struct roots_t root);
double discr(struct coeffs_t coef);
int linSolve(double b, double c, double *x);

struct coeffs_t
{
    double a = 0;
    double b = 0;
    double c = 0;
};

struct roots_t
{
    double x1 = 0;
    double x2 = 0;
    int nRoots = -2;
};

int main()
{
    struct coeffs_t sq;
    struct roots_t root;

    printf("# SquareSolver\n"
           "# Made for Summer school MIPT\n");

    printf("Enter a, b, c coefficients:\n");

    scanCoefs(&sq);

    sqSolve(sq, &root);
    printRoots(root);

    return 0;
}

void sqSolve(struct coeffs_t coef, struct roots_t *root)
{
    assert(root != NULL);

    assert(isfinite(coef.a));
    assert(isfinite(coef.b));
    assert(isfinite(coef.c));

    if (isZero(coef.a))
    {
        root -> nRoots = linSolve(coef.b, coef.c, &(root -> x1));
        return;
    }

    double D = discr(coef);
    if (isZero(D))
    {
        root -> x1 = -coef.b/(2*coef.a);
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
    assert(isfinite(a));
    return fabs(a) < EPSILON;
}

void scanCoefs(struct coeffs_t *sq)
{
    assert(sq != NULL);
    while(scanf("%lg %lg %lg", &(sq -> a), &(sq -> b), &(sq -> c)) != 3)  {
        int ch = EOF;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Try again\n");
    }
}

void printRoots(struct roots_t root){
    switch(root.nRoots)
    {
        case 0:
            printf("No real roots");
            break;

        case 1:
            printf("x = %lg\n", root.x1);
            break;

        case 2:
            printf("x1 = %lg\nx2 = %lg\n", root.x1, root.x2);
            break;

        case INF_ROOTS:
            printf("Infinite roots\n");
            break;

        default:
            printf("ERROR nRoots = %d\n", root.nRoots);
            break;
    }
}

int linSolve(double b, double c, double *x)
{
    assert(x != NULL);
    assert(isfinite(b));
    assert(isfinite(c));

    if (isZero(b))
    {
        if (isZero(c))
            return INF_ROOTS;
        return 0;
    }
    *x = -c/b;
    return 1;
}

double discr(struct coeffs_t coef)
{
    assert(isfinite(coef.a));
    assert(isfinite(coef.b));
    assert(isfinite(coef.c));

    return coef.b*coef.b - 4*coef.a*coef.c;
}
