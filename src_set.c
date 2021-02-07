#include "ft_printf.h"

void set_star(va_list ap, t_flags *flags)
{
    int arg;

    if (flags->star)
    {
        arg = va_arg(ap, int);
        if (arg < 0)
        {
            flags->zero = 0;
            flags->width_minus = 1;
            arg *= -1;
        }
        flags->width = arg;
    }
    if (flags->dot_star)
    {
        arg = va_arg(ap, int);
        flags->dot_width = arg;
    }
}

void set_arg(char *percent, t_flags *flags, va_list ap)
{
    if (*percent == 's')
    {
        flags->string = va_arg(ap, char *);
        if (flags->string == NULL)
            flags->string = "(null)";
        // flags->dot = 0;
        // flags->dot_width = 0;
    }
        // while (flags->string[i] && i < flags->dot_width)
        //     i++;
    else if (*percent == 'd' || *percent == 'i' || *percent == 'c' || *percent == '%')
    {
        flags->arg = va_arg(ap, int);
        // printf("\narg: %d\n", flags->arg);
    }
    else if (*percent == 'u' || *percent == 'x' || *percent == 'X')
        flags->arg = va_arg(ap, unsigned int);
    else if (*percent == 'p')
    {
        flags->arg = (long long)va_arg(ap, void *);
        flags->width -= 2;
        if (flags->arg == 0)
            flags->width--;   
    }
}

int check_len(long long n, t_flags *flags, int type)
{
    int len;
    
    len = 1;
    if (type == 0)
    {
        if (n == 0 && flags->dot && flags->dot_width == 0)
            return (0);
        if (n < 0)
        {
            n *= -1;
            flags->arg *= -1;
            flags->minus = 1;
        }
        while ((n /= 10) != 0)
            len++;
    }
    else if (type == 1)
    {
        while ((n /= 16) != 0)
            len++;
    }
    return (len);
}

int set_len(char *percent, t_flags *flags)
{
    int len;

    len = 0;
    if (*percent == 's')
    {
        if (flags->dot)
        {
            while (flags->string[len] && (len < flags->dot_width || flags->dot_width < 0))
                len++;
        }
        else
        {
            while (flags->string[len])
                len++;
        }
        if (flags->dot_width > len || flags->dot_width < 0)
        {
            flags->dot = 0;
            flags->dot_width = 0;
        }

    }
    else if (*percent == 'd' || *percent == 'i' || *percent == 'u')
    {
        len = check_len(flags->arg, flags, 0);
        // printf("\nlen: %d\n", len);
    }
    else if (*percent == 'c' || *percent == '%')
        len = 1;
    else if (*percent == 'x' || *percent == 'X')
        len = check_len(flags->arg, flags, 1);
    return (len);
}


void set_width(t_flags *flags, int len)
{
    if(flags->minus)
        flags->width--;
    if (flags->zero && flags->dot && flags->dot_width >= 0)
    {
        flags->print_zero = flags->dot_width - len;
        if (flags->print_zero > 0)
            flags->print_space = flags->width - flags->dot_width;
        else
            flags->print_space = flags->width - len;
    }
    else if (flags->zero)
    {
        flags->print_zero = flags->width - len;
    }
    else if (flags->width && flags->dot)
    {
        // printf("\nwidth: %d\n", flags->width);
        // printf("\nlen: %d\n", len);
        flags->print_zero = flags->dot_width - len;
        if (flags->print_zero > 0)
            flags->print_space = flags->width - flags->dot_width;
        else
        {
            flags->print_space = flags->width - len;
        }
    }
    else
    {
        // printf("\nlen: %d\n", len);
        // printf("\nwidth: %d\n", flags->width);
        flags->print_space = flags->width - len;
        // printf("\nspace: %d\n", flags->print_space);
        flags->print_zero = flags->dot_width - len;
    }
}