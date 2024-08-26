//! @file
#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include "consts.h"

//! @brief Структура, содержащая коэффициенты и эталонные значения для тестов функции sqSolve()
struct test_t
{
    int num;            ///< Номер теста
    coeffs_t coef;      ///< Структура типа coeffs_t, содержащая коэффициенты
    roots_t root;       ///< Структура типа roots_t, содержащая эталонные корни
};

//! @brief Запускает тесты из файла с именем fname, использует freadTests() и runTest()
//!
//! @param      [IN]    fname     константная строка с названием файла
//! @return     Возвращает 0, если тест не пройден или при ошибке, 1 - при успешном выполнении теста
int frunTests(const char *fname);

//! @brief Читает тесты из файла fname в массив testp
//!
//! @param      [IN]    fname     константная строка с названием файла
//! @param      [OUT]   testp     указатель на первый элемент массива
//! @return     Возвращает 0 при ошибке открытия файла, 1 - в обратном случае
int freadTests(const char *fname, struct test_t **testp);

//! @brief (Устаревшее) Выполняет тесты из внутреннего массива типа struct test_t
//! @return     Возвращает 0, если тесты не пройдены, 1 - при успешном выполнении теста
int runTests();

//! @brief Тестирует функцию sqSolve, используя данные из test
//!
//! @param      [IN]    test     Структура с эталонными данными
//! @return     Возвращает 0, если тест не пройден, 1 - при успешном выполнении теста
int runTest(struct test_t test);

#endif // TESTS_H_INCLUDED
