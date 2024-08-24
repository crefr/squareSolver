//! @file
#ifndef ARGVPR_INCLUDED
#define ARGVPR_INCLUDED

static const int MAXLIN = 100;

//! @brief Структура, хранящая данные о флаге командной строки
struct argvEx_t
{
    unsigned int valtype;       ///< Номер типа значения
    const char *fname;          ///< Название флага
    const char *help;           ///< То, что выведется в --help про этот флаг
};

//! @brief Объединение, хранящее значение флага
union fvals
{
    unsigned int bl : 1;  ///< Значение типа bool
    int in;               ///< Значение типа int
    double dbl;           ///< Значение типа double
    char str[MAXLIN];     ///< Строка
};

//! @brief Обрабатывает аргументы командной строки, примеры которых лежат в массиве структур argvEx_t в argvprocessing.cpp, заполняет массив fval значениями флагов
//! @param      [IN]    argc    argc из main, количество аргументов
//! @param      [IN]    argv    указатель на массив строк argv
//! @param      [OUT]   fval    массив типа union fvals, в который записываются значения флагов
//! @return     Возвращает BAD, если произошла какая-то ошибка, GOOD - если все хорошо (константы, заданы в consts.h)
int argvReceive(int argc, char **argv, union fvals *fval);

//! @brief Действует в зависимости от значений флагов в fval
//! @param      [IN]    fval    массив типа union fvals со значениями флагов
//! @return     Может вернуть EXIT_ (выйти из программы), ERROR_ (ошибка) и 0 (все хорошо)
int argvHandler(union fvals *fval);

//! @brief Выставляет начальные значения массива fval
//! @param      [OUT]    fval    массив типа union fvals со значениями флагов
void setFlags(union fvals *fval);


#endif
