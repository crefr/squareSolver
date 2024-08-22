//! @file

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//#include "TXLib.h"
#include <ctype.h>

#include "colors.h"

//! @brief  Структура, содержащая 3 коэффициента квадратного уравнения (a, b, c)
struct coeffs_t
{
    double a; ///< коэффициент a
    double b; ///< коэффициент b
    double c; ///< коэффициент c
};

//! @brief  Структура, 2 переменные для корней квадратного уравнения и nRoots, содержащая количество корней
struct roots_t
{
    double x1;      ///< первый корень
    double x2;      ///< второй корень
    int nRoots;     ///< количество корней
};

struct test_t
{
    int num;
    coeffs_t coef;
    roots_t root;
};

struct flags_t
{
    unsigned int m : 1;
    unsigned int h : 1;
    unsigned int c : 1;
};

struct flags_t modes = {0, 0, 1};

const int INF_ROOTS = -1;
const double EPSILON = 0.00001;

const int ERROR_ = -10;
enum EXITS {BAD, GOOD};

void sqSolve(struct coeffs_t coef, struct roots_t *root);
int isZero(const double a);
int scanCoefs(struct coeffs_t *coeffs);
void printRoots(struct roots_t root);
double discr(struct coeffs_t coef);
int linSolve(double b, double c, double *x);
int runTest(struct test_t test);
int equals(double a, double b);
int runTests(struct test_t tests[], int len);
bool eqRoots(roots_t root1, roots_t root2);
int argvReceive(int argc, char **argv);

#include "tests.h"

#ifndef TESTS_H_INCLUDED
    struct test_t tests[0];
    const int TESTNUM = 0;
#endif

int main(int argc, char *argv[])
{
    if (argvReceive(argc, argv) == BAD)
    {
        printf("CMD args ERROR\n");
        return ERROR_;
    }

    if (modes.h == 1)
    {
        printf("#######################################################\n");
        printf("-m        \tswitches mode to 0 or 1 (-m 0 and -m 1)\n"
               "--help, -h\tstandard --help\n"
               "-c        \tswitches color mode to 0 or 1 (-c 0 and -c 1)\n");
        printf("#######################################################\n");
        return 0;
    }

    if (modes.m == 1)
    {
        if (!runTests(tests, TESTNUM))
        {
            printf("TESTING FAILED\n");
            return ERROR_;
        }
        return 0;
    }
    struct coeffs_t sq;
    struct roots_t root;

    printf("# SquareSolver\n"
           "# Made for Summer school MIPT\n");

    printf("Enter a, b, c coefficients (only one number in each line): \n");

    if (scanCoefs(&sq) == 0)
    {
        printf((modes.c) ? RED "!!!INPUT ERROR!!!" : "!!!INPUT ERROR!!!");
        return ERROR_;
    }

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
    double *ptrs[] = {&(sq -> a), &(sq -> b), &(sq -> c)};  // б≤б≤б≤б≤б≤б≤ б≤б≤б≤б≤б≤б≤б≤б≤б≤б≤ б≤б≤б≤ for
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

//! @brief Печатает корни из структуры roots_t
//!
//! @param      [IN]    root    структура с корнями типа roots_t

void printRoots(struct roots_t root){
    switch(root.nRoots)
    {
        case 0:
            printf((modes.c) ? RED "No real roots" RESET_C : "No real roots");
            break;

        case 1:
            printf((modes.c) ? GREEN "x = %lg\n" RESET_C : "x = %lg\n", root.x1);
            break;

        case 2:
            printf((modes.c) ? GREEN "x1 = %lg\nx2 = %lg\n" RESET_C : "x1 = %lg\nx2 = %lg\n", root.x1, root.x2);
            break;

        case INF_ROOTS:
            printf((modes.c) ? GREEN "Infinite roots\n" RESET_C : "Infinite roots\n");
            break;

        default:
            printf((modes.c) ? GREEN "ERROR nRoots = %d\n" RESET_C : "Infinite roots\n" , root.nRoots);
            break;
    }
}

//! @brief Решает линейное уравнение вида bx + c = 0
//!
//! @param      [IN]    b   коэффициент b
//! @param      [IN]    c   коэффициент c
//! @param      [OUT]   x   указатель на корень
//! @return     Возвращает количество корней (1, 0 или INF_ROOTS)

int linSolve(const double b, const double c, double *x)
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

int equals(const double a, const double b)
{
    assert(isfinite(a));
    assert(isfinite(b));
    return (fabs(a - b) < EPSILON) ? 1: 0;
}

int runTest(struct test_t test)
{
    struct roots_t root;
    sqSolve(test.coef, &root);
    if (!equals(test.root.nRoots, root.nRoots) || !eqRoots(test.root, root))
    {
        #ifdef _TX_MODULE
            txSetConsoleAttr(4) meow
        #endif
        printf((modes.c) ? RED "Error Test %d:\na = %lg, b = %lg, c = %lg\n"
               "x1 = %lg, x2 = %lg, nRoots = %d\n"
               "Expected:\nx1 = %lg, x2 = %lg, nRoots = %d\n" RESET_C
               : "Error Test %d:\na = %lg, b = %lg, c = %lg\n"
               "x1 = %lg, x2 = %lg, nRoots = %d\n"
               "Expected:\nx1 = %lg, x2 = %lg, nRoots = %d\n",
               test.num, test.coef.a, test.coef.b, test.coef.c, root.x1, root.x2, root.nRoots,
               test.root.x1, test.root.x2, test.root.nRoots);
        #ifdef _TX_MODULE
            txSetConsoleAttr(7) meow
        #endif
        return 0;
    }
    #ifdef _TX_MODULE
        txSetConsoleAttr(2) meow
    #endif
    printf((modes.c) ? GREEN "Test %d Correct\n" RESET_C : "Test %d Correct\n", test.num);

    #ifdef _TX_MODULE
        txSetConsoleAttr(7) meow
    #endif
    return 1;
}

int runTests(struct test_t test[], int len)
{
    assert(test != NULL);
    for (int i = 0; i < len; i++)
    {
        if (runTest(test[i]) == 0)
            return 0;
    }
    return 1;
}

bool eqRoots(roots_t root1, roots_t root2)
{
    if(equals(root1.x1, root2.x1) && equals(root1.x2, root2.x2))
        return 1;
    if(equals(root1.x1, root2.x2) && equals(root1.x2, root2.x1))
        return 1;
    return 0;
}
int argvReceive(int argc, char **argv)
{
    assert(argv!=NULL);

    enum conf_state {READY, VAL};
    int mconf = VAL;
    int cconf = VAL;

    for(int i = 1; i < argc; i++)
    {
        if (argc == 2 && (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0))
        {
            modes.h = 1;
            return GOOD;
        }
        else if (strcmp("-m", argv[i]) == 0 && mconf == VAL && cconf == VAL)
            mconf = READY;
        else if (strcmp("-c", argv[i]) == 0 && mconf == VAL && cconf == VAL)
            cconf = READY;

        else if (mconf == READY)
        {
            mconf = VAL;
            if (strcmp("0", argv[i]) == 0)
                modes.m = 0;
            else if (strcmp("1", argv[i]) == 0)
                modes.m = 1;
            else
                return BAD;
        }

        else if (cconf == READY)
        {
            cconf = VAL;
            if (strcmp("0", argv[i]) == 0)
                modes.c = 0;
            else if (strcmp("1", argv[i]) == 0)
                modes.c = 1;
            else
                return BAD;
        }
        else
            return BAD;
    }

    if (mconf == READY || cconf == READY)
        return BAD;
    return GOOD;
}

/*
структуры для командной строки
цветной printf
*/
