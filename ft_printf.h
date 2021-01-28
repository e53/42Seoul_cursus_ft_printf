#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int ft_printf(const char *s, ...);
void	*ft_memset(void *str, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);
int		itoa_len(long long num);

typedef struct s_flags{
    int len;
    int minus;
    int zero;
    int width;
    int dot;
    int dot_width;
    int star;
    int dot_star;
} t_flags;