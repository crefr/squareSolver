//! @file
#ifndef SQMATH_INCLUDED
#define SQMATH_INCLUDED

//! @brief Решает квадратное уравнение вида ax^2 + bx + c = 0.
//! Коэффициенты берет из структуры coeffs_t, корни пишет в структуру roots_t
//!
//! @param      [IN]    coef    структура с коэффициентами
//! @param      [OUT]   root    указатель на структуру с корнями
void sqSolve(struct coeffs_t coef, struct roots_t *root);

//! @brief Приближенно сравнивает a с 0. Погрешность определяется константой EPSILON
//!
//! @param      [IN]    a   сравниваемое число
//! @return     1, если число сравнимо с нулем, 0 - если нет
int isZero(const double a);

//! @brief Считает дискриминант, используя коэффициенты из структуры типа coeffs_t
//!
//! @param      [IN]    coef    структура с коэффициентами
//! @return     Возвращает значение дискриминанта
double discr(struct coeffs_t coef);

//! @brief Решает линейное уравнение вида bx + c = 0
//!
//! @param      [IN]    b   коэффициент b
//! @param      [IN]    c   коэффициент c
//! @param      [OUT]   x   указатель на корень
//! @return     Возвращает количество корней (1, 0 или INF_ROOTS)
int linSolve(double b, double c, double *x);

//! @brief С погрешностью EPSILON сравнивает 2 числа типа double
//! @param      [IN]    a   Первое сравниваемое число
//! @param      [IN]    b   Второе сравниваемое число
//! @return     Возвращает 1, если числа приближенно равны и 0 - в обратном случае
int equals(double a, double b);

//! @brief С погрешностью EPSILON сравнивает корни типа roots_t
//! @param      [IN]    root1   Структура типа roots_t, содержащая корни
//! @param      [IN]    root2   Структура типа roots_t, содержащая корни
//! @return     Возвращает 1, если числа структура содержат одинаковые корни с точностью до EPSILON (порядок не важен) и 0 - в обратном случае
bool eqRoots(roots_t root1, roots_t root2);

#endif
