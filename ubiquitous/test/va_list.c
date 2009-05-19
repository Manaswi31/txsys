#include <stdarg.h>

int _printf(const char* fmt, va_list ap)
{
}

int printf(char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    _printf(fmt,ap);
    va_end(ap);
}

int main()
{
    printf("%s: %d\n", message, number);
}
