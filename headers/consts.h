//! @file
#ifndef CONSTS_INCLUDED
#define CONSTS_INCLUDED

const int INF_ROOTS = -1;
const double EPSILON = 1e-5;

const int ERROR_ = -10;
const int EXIT_ = -20;
enum EXITS {BAD = 0, GOOD, EXIT};
enum flags {H = 0, HELP, M, C, F};

const int MAXLINE = 100;

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
#endif
