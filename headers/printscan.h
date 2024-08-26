//! @file
#ifndef PRINTSCAN_INCLUDED
#define PRINTSCAN_INCLUDED

//! @brief Записывает вводимые коэффициенты в структуру coeffs_t, в случае неправильного ввода возвращает 0
//!
//! @param      [OUT]   sq    указатель на структуру, в которую запишутся коэффициенты
//! @return Возвращает 1, если все хорошо, 0 - в обратном случае
int scanCoefs(struct coeffs_t *coeffs);


//! @brief Печатает корни из структуры roots_t
//!
//! @param      [IN]    root    структура с корнями типа roots_t
void printRoots(struct roots_t root);

#endif
