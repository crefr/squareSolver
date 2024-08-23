#ifndef CONSTS_INCLUDED
#define CONSTS_INCLUDED

const int INF_ROOTS = -1;
const double EPSILON = 0.00001;

const int ERROR_ = -10;
enum EXITS {BAD, GOOD};

const int MAXLINE = 100;

struct argvEx_t
{
    unsigned int haveVal : 1;
    char fname[MAXLINE];
    unsigned int fval : 1;
    const char *help;

};

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

struct flags_t
{
    unsigned int m : 1;
    unsigned int h : 1;
    unsigned int c : 1;
};

enum flags {H = 0, HELP, M, C};

#endif
