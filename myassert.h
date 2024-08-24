//! @file

#ifndef MYASSERT_INCLUDED
#define MYASSERT_INCLUDED

#include <stdlib.h>

#include "colors.h"
#include "colPrintf.h"

//! @brief При ложности arg рубит программу, выдавая номер ассерта, название файла, номер строки, название функции и, собственно, сам arg
#define MYASSERT(arg)                                                                                               \
            do{                                                                                                     \
                if (!(arg))                                                                                         \
                {                                                                                                   \
                    colPrintf(RED, "\tMYASSERT #%d: ERROR in file: %s, function %s(), line %d\n \t>>> " #arg  "\n", \
                                __COUNTER__ + 1, __FILE__, __FUNCTION__, __LINE__);                                 \
                    exit(1);                                                                                        \
                }                                                                                                   \
            } while(0)
#endif
