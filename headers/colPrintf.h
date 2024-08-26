//! @file
#ifndef COLPRINTF_INCLUDED
#define COLPRINTF_INCLUDED

//! @brief Функция, выставляющая значение colFlag
//! @param      [IN]    colF    Значение флага, которое нужно выставить
void setColFlag(const unsigned int colF);

//! @brief (Устаревшее) Если colFlag == 1, текст окрашивается с помощью цветовой строки color, в остальном - обычный printf
//! @param      [IN]    color    Константная строка цвета (подобные описаны в colors.h)
//! @param      [IN]    format   Форматируемая окрашивающаяся строка
void colPrintf_old(const char *color, const char *format, ...);

//! @brief Если colFlag == 1, текст окрашивается с помощью цветовой строки color, в остальном - обычный printf
//! @param      [IN]    color    Константная строка цвета (подобные описаны в colors.h)
//! @param      [IN]    format   Форматируемая окрашивающаяся строка
void colPrintf(const char *color, const char *format, ...);

#endif
