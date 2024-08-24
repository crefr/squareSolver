#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include "myisfinite.h"

int myisfinite(double a)
{
    int size = sizeof(double) * 8;
        // это из формулы, данной в стандарте:
    int w = lround(4 * log2(size)) - 13;
        //маска на все заполненные биты в E
    uint64_t mask = (1ULL << w) - 1;

        //забавный костыль
    double *p = &a;
    uint64_t bits = *( (uint64_t*)p );
    if ( ((bits>>(size - w - 1)) & mask) == mask )
        return 0;
    return 1;
}

int myINForNAN(double a)
{
    int size = sizeof(double) * 8;
        // это из формулы, данной в стандарте
    int w = lround(4 * log2(size)) - 13;
        //маска на биты мантиссы (если она ноль, то это INF, иначе NAN)
    uint64_t mask = (1ULL << (size - w - 1)) - 1;
        //забавный костыль
    double *p = &a;
    uint64_t bits = *( (uint64_t*)p );

    if ((bits & mask) == 0)
    {
        if ((bits >> (size - 1)) != 0)
            return ISNEGINF;
        else
            return ISINF;
    }
    return ISNAN;
}
