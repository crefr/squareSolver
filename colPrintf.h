#ifndef COLPRINTF_INCLUDED
#define COLPRINTF_INCLUDED

void setColFlag(unsigned int colF);
void colPrintf_old(const char *color, const char *format, ...);
void colPrintf(const char *color, const char *format, ...);

#endif
