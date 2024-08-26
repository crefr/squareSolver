/// @file
#ifndef MYISFINITE_INCLUDED
#define MYISFINITE_INCLUDED

/// @brief Возможные возвращаемые значения функции isNotFinite()
enum infornan {ISNEGINF = -1, ISNAN, ISINF};

/**
 * @brief Определяет чем из следующего является число a (заведомо неадекватное): NAN, INFINITY, -INFINITY
 *
 * @param   a   [IN]    Собственно число, обязательно неадекватное
 * @return int  Число из enum finites - ISNAN, если число - NAN; ISINF, если INFINITY; ISNEGINF, если -INFINITY
 */
int myINForNAN(double a);

/**
 * @brief Буквально isfinite, только мой - если число не NAN, INF, -INF, возвращает 1
 *
 * @param   a     [IN]    Собственно число
 * @return  int   1, если число адекватно (не NAN, INF, -INF), 0 - в обратном случае
 */
int myisfinite(double a);

#endif
