#include <stdio.h>
#include <stdarg.h>

#include "colors.h"
#include "colPrintf.h"

static unsigned int colfl = 0;

void setColFlag(unsigned int colF)
{
    colfl = colF;
}

void colPrintf_old(const char *color, const char *format, ...)
{
    if (colfl)
        printf("%s", color);
    va_list ap;
    va_start(ap, format);

    const char *p;
    int lflag = 0;
    for (p = format; *p != '\0'; p++)
    {
        if(*p != '%' && !lflag)
        {
            putchar(*p);
            continue;
        }

        if (lflag)
            lflag = 0;
        else
            p++;

        switch(*p)
        {
            case 'l':
                lflag = 1;
                break;
            case 'd':
                printf("%d", va_arg(ap, int));
                break;
            case 'f': case 'g':
                printf("%lg", va_arg(ap, double));
                break;
            case 's':
                printf("%s", va_arg(ap, char*));
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
    printf(RESET_C);
}

void colPrintf(const char *color, const char *format, ...)
{
    if (colfl)
        printf("%s", color);
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf(RESET_C);
}
