#include <unistd.h>
#include <stdarg.h>

void put_str(char *str, int *len)
{
    if (!str)
        str = "(null)";
    while (*str)
        *len += write(1, str++, 1);
}

void put_digit(long long int num, int base, int *len)
{
    char *hexa = "0123456789abcdef";

    if (num < 0)
    {
        *len += write(1, "-", 1);
        num = -num;
    }
    if (num >= base)
        put_digit(num / base, base, len);
    *len += write(1, &hexa[num % base], 1);
}

int ft_printf(const char *format, ...)
{
    int len = 0;
    va_list args;
    va_start(args, format);

    while (*format)
    {
        if (*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
        {
            format++;
            if (*format == 's')
                put_str(va_arg(args, char *), &len);
            else if (*format == 'd')
                put_digit((long long int)va_arg(args, int), 10, &len);
            else if (*format == 'x')
                put_digit((long long int)va_arg(args, unsigned int), 16, &len);
        }
        else
            len += write(1, format, 1);
        format++;
    }

    va_end(args);
    return len;
}
