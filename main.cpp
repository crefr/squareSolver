//! @file

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

const int INF_ROOTS = -1;
const double EPSILON = 0.00001;

void sqSolve(struct coeffs_t coef, struct roots_t *root);
int isZero(const double a);
int scanCoefs(struct coeffs_t *coeffs);
void printRoots(struct roots_t root);
double discr(struct coeffs_t coef);
int linSolve(double b, double c, double *x);


//! @brief  Структура, содержащая 3 коэффициента квадратного уравнения (a, b, c)
struct coeffs_t
{
    double a = 0; ///< коэффициент a
    double b = 0; ///< коэффициент b
    double c = 0; ///< коэффициент c
};

//! @brief  Структура, 2 переменные для корней квадратного уравнения и nRoots, содержащая количество корней
struct roots_t
{
    double x1 = 0;      ///< первый корень
    double x2 = 0;      ///< второй корень
    int nRoots = -2;    ///< количество корней
};

int main()
{
    struct coeffs_t sq;
    struct roots_t root;

    printf("# SquareSolver\n"
           "# Made for Summer school MIPT\n");

    printf("Enter a, b, c coefficients (only one number in each line): \n");

    if (scanCoefs(&sq) == 0)
        return 1;

    sqSolve(sq, &root);
    printRoots(root);

    return 0;
}

//! @brief Решает квадратное уравнение вида ax^2 + bx + c = 0.
//! Коэффициенты берет из структуры coeffs_t, корни пишет в структуру roots_t
//!
//! @param      [IN]    coef    структура с коэффициентами
//! @param      [OUT]   root    указатель на структуру с корнями


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


//! @brief Приближенно сравнивает a с 0. Погрешность определяется константой EPSILON
//!
//! @param      [IN]    a   сравниваемое число
//! @return     1, если число сравнимо с нулем, 0 - если нет

int isZero(const double a)
{
    assert(isfinite(a));
    return fabs(a) < EPSILON;
}

//! @brief Записывает вводимые коэффициенты в структуру coeffs_t, в случае неправильного ввода возвращает 0
//!
//! @param      [OUT]   sq      указатель на структуру, в которую запишутся коэффициенты
//! @return Возвращает 1, если все хорошо, 0 - в обратном случае

int scanCoefs(struct coeffs_t *sq)
{
    assert(sq != NULL);
    double *ptrs[] = {&(sq -> a), &(sq -> b), &(sq -> c)};  // массив указателей для for
    for (int i = 0; i <= 2; i++){
        scanf("%lg", ptrs[i]);
        int ch = EOF;
        if ((ch = getchar()) != '\n' && ch != EOF)
        {
            printf("!!!input ERROR!!!");
            return 0;
        }
    }
    return 1;
}

//! @brief Печатает корни из структуры roots_t
//!
//! @param      [IN]    root    структура с корнями типа roots_t

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

//! @brief Решает линейное уравнение вида bx + c = 0
//!
//! @param      [IN]    b   коэффициент b
//! @param      [IN]    c   коэффициент c
//! @param      [OUT]   x   указатель на корень
//! @return     Возвращает количество корней (1, 0 или INF_ROOTS)

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

//! @brief Считает дискриминант, используя коэффициенты из структуры типа coeffs_t
//!
//! @param      [IN]    coef    структура с коэффициентами
//! @return     Возвращает значение дискриминанта

double discr(struct coeffs_t coef)
{
    assert(isfinite(coef.a));
    assert(isfinite(coef.b));
    assert(isfinite(coef.c));

    return coef.b*coef.b - 4*coef.a*coef.c;
}
