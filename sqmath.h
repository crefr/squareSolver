#ifndef SQMATH_INCLUDED
#define SQMATH_INCLUDED

void sqSolve(struct coeffs_t coef, struct roots_t *root);
int isZero(const double a);
double discr(struct coeffs_t coef);
int linSolve(double b, double c, double *x);
int equals(double a, double b);
bool eqRoots(roots_t root1, roots_t root2);

#endif
