#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>

typedef struct   s_printf
{
    int width;
    int precision;
    int nbtotal;
    va_list args;
}               t_printf;

void ft_init_struct(t_printf *env)
{
    env->width = 0;
    env->precision = -1;
    env->nbtotal = 0;
}

void ft_reinit_struct(t_printf *env)
{
    env->width = 0;
    env->precision = -1;
}

void ft_putchar(char c, t_printf *env)
{
    write(1, &c, 1);
    env->nbtotal += 1;
}

void ft_putstr(char *s, t_printf *env)
{
    int i = 0;
    while (s[i])
    {
        ft_putchar(s[i], env);
        i++;
    }
}

void ft_putstr_size(char *s, int size, t_printf *env)
{
    int i = 0;
    while (s[i] && i < size)
    {
        ft_putchar(s[i], env);
        i++;
    }
}

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int ft_nbrlen(long nb, t_printf *env)
{
    int i = 0;
    if (nb == 0 && env->precision != 0)
        return 1;
    if (nb < 0)
    {
        nb *= -1;
        i++;
    }
    while (nb > 9)
    {
        nb /= 10;
        i++;
    }
    if (nb != 0)
        i++;
    return i;
}

void ft_write_s(char *arg, t_printf *env)
{
    int size = 0;
    if (arg == NULL)
        arg = "(null)";
    if (env->precision > -1 && env->precision < ft_strlen(arg))
        size = env->precision;
    else    
        size = ft_strlen(arg);
    if (env->width > 0 && env->width > size)
    {
        env->width -= size;
        while (env->width-- > 0)
            ft_putchar(32, env);
    }
    if (size != ft_strlen(arg))
        ft_putstr_size(arg, size, env);
    else
        ft_putstr(arg, env);
}

void ft_write_d(long arg, t_printf *env)
{
    int size = 0;
    int sizearg = ft_nbrlen(arg, env);
    if (env->precision > sizearg)
        size = env->precision;
    else
        size = sizearg;
    if (env->width > 0 && env->width > size)
    {
        env->width -= size;
        while(env->width-- > 0)
            ft_putchar(32, env);
    }
    if(arg < 0)
    {
        ft_putchar('-', env);
        arg *= -1;
    }
    while (size-- > sizearg)
        ft_putchar('0', env);
    char buffer[12];
    int i = 11;
    int tmp = 0;
    buffer[i--] = '\0';
    if (arg == 0 && env->precision != 0)
        buffer[i--] = '0';
    while (arg)  
    {
        tmp = arg % 10;
        buffer[i--] = tmp + '0';
        arg /= 10;
    }
    ft_putstr(buffer + i + 1, env);
}

void ft_write_x(unsigned int arg, t_printf *env)
{
    char buffer[12];
    int i = 11;
    int tmp = 0;
    buffer[i--] = '\0';
    if (arg == 0 && env->precision != 0)
        buffer[i--] = '0';
    while (arg)  
    {
        tmp = arg % 16;
        if (tmp > 9)
            buffer[i--] = tmp + 'a' - 10;
        else
            buffer[i--] = tmp + '0';
        arg /= 16;
    }
    int size = 0;
    int sizearg = ft_strlen(buffer + i + 1);
    if(env->precision > sizearg)
        size = env->precision;
    else
        size = sizearg;
    if (env->width > 0 && env->width > size)
    {   
        env->width -= size;
        while(env->width-- > 0)
            ft_putchar(32, env);
    }
    while (size-- > sizearg)
        ft_putchar('0', env);
   
    
    ft_putstr(buffer + i + 1, env);
}

void ft_parse(const char *format, t_printf *env)
{
    int i = -1;

    while (format[++i])
    {
        if (format[i] == '%')
        {
            i++;
            ft_reinit_struct(env);
            if (format[i] >= '0' && format[i] <= '9')
            {
                while (format[i] >= '0' && format[i] <= '9')
                {
                    env->width = env->width * 10 + format[i] - '0';
                    i++;
                }
            }
            if (format[i] == '.')
            {   
                i++;
                env->precision = 0;
                while (format[i] >= '0' && format[i] <= '9')
                {   
                    env->precision = env->precision * 10 + format[i] - '0';
                    i++;
                }
            }
            if (format[i] == 's')
                ft_write_s(va_arg(env->args, char *), env);
            else if (format[i] == 'd')
                ft_write_d(va_arg(env->args, int), env);    
            else if (format[i] == 'x')
                ft_write_x(va_arg(env->args, unsigned int), env);
        }
        else
            ft_putchar(format[i], env);
    }
}

int ft_printf (const char *format, ...)
{
    t_printf env;
    ft_init_struct(&env);
    va_start(env.args, format);
    ft_parse(format, &env);
    va_end(env.args);
    return(env.nbtotal);
}
/*
int main(void)
{
    int a = 0;
    int b = 0;
    int valx1 = 0;
	int valx2 = 1;
	int valx3 = -1;
	int valx4 = 10;
	int valx5 = -10;
	int valx6 = 102;
	int valx7 = -101;
	int valx8 = 1021;
	int valx9 = -1011;
	int valx10 = INT_MAX;
	int valx11 = INT_MIN;
	int valx12 = CHAR_MAX;
	int valx13 = CHAR_MIN;
	int valx14 = UINT_MAX;
	int valx15 = UINT_MAX + 1;
	int valx16 = -42;

    int vald1 = 0;
	int vald2 = 1;
	int vald3 = -1;
	int vald4 = 10;
	int vald5 = -10;
	int vald6 = 102;
	int vald7 = -101;
	int vald8 = 1021;
	int vald9 = -1011;
	int vald10 = INT_MAX;
	int vald11 = INT_MIN;
	int vald12 = CHAR_MAX;
	int vald13 = CHAR_MIN;
	int vald14 = UINT_MAX;
	int vald15 = UINT_MAX + 1;
	int vald16 = -42;
	int vald17 = LONG_MAX;
	int vald18 = LONG_MIN;

    char *val1 = "";
	char *val2 = "0";
	char *val3 = "1";
	char *val4 = "123";
	char *val5 = "4567";
	char *val6 = NULL;

    ft_printf(" test 1 %d %15.15d\n", 42, 543544354);
    printf(" test 1 %d %15.15d\n", 42, 543544354);
    printf("%%x\n");
    a = ft_printf("test : %x |\n",valx1);
	b = printf("test : %x |\n",valx1);
	printf("test retour :%d %d \n", a ,b);
	a = ft_printf("test :%x\n",valx2);
	b = printf("test :%x\n",valx2);
	printf("test retour :%d %d \n", a ,b);
	a = ft_printf("test :%x\n",valx3);
	b = printf("test :%x\n",valx3);
	printf("test retour :%d %d \n", a ,b);
	a = ft_printf("test :%x\n",valx4);
	b = printf("test :%x\n",valx4);
	printf("test retour :%d %d \n", a ,b);
	a = ft_printf("test :%x\n",valx5);
	b = printf("test :%x\n",valx5);
	printf("test :%d %d \n", a ,b);
	a = ft_printf("test :%x\n",valx6);
	b = printf("test :%x\n",valx6);
	printf("test retour :%d %d \n", a ,b);
	a = ft_printf("%x\n",valx7);
	b = printf("%x\n",valx7);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx8);
	b = printf("%x\n",valx8);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx9);
	b = printf("%x\n",valx9);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx10);
	b = printf("%x\n",valx10);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx11);
	b = printf("%x\n",valx11);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx12);
	b = printf("%x\n",valx12);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx13);
	b = printf("%x\n",valx13);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx14);
	b = printf("%x\n",valx14);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx15);
	b = printf("%x\n",valx15);
	printf("%d %d \n", a ,b);
	a = ft_printf("%x\n",valx16);
	b = printf("%x\n",valx16);
	printf("%d %d \n", a ,b);

    printf("%%d");
    a = ft_printf("%d\n",vald1);
	b = printf("%d\n",vald1);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald2);
	b = printf("%d\n",vald2);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald3);
	b = printf("%d\n",vald3);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald4);
	b = printf("%d\n",vald4);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald5);
	b = printf("%d\n",vald5);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald6);
	b = printf("%d\n",vald6);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald7);
	b = printf("%d\n",vald7);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald8);
	b = printf("%d\n",vald8);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald9);
	b = printf("%d\n",vald9);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald10);
	b = printf("%d\n",vald10);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald11);
	b = printf("%d\n",vald11);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald12);
	b = printf("%d\n",vald12);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald13);
	b = printf("%d\n",vald13);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald14);
	b = printf("%d\n",vald14);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald15);
	b = printf("%d\n",vald15);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald16);
	b = printf("%d\n",vald16);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald17);
	b = printf("%d\n",vald17);
	printf("%d %d \n", a ,b);
	a = ft_printf("%d\n",vald18);
	b = printf("%d\n",vald18);
	printf("%d %d \n", a ,b);   

    printf("%%s\n");
    a = ft_printf("%s\n",val1);
	b = printf("%s\n",val1);
	printf("%d %d \n", a ,b);
	a = ft_printf("%s\n",val2);
	b = printf("%s\n",val2);
	printf("%d %d \n", a ,b);
	a = ft_printf("%s\n",val3);
	b = printf("%s\n",val3);
	printf("%d %d \n", a ,b);
	a = ft_printf("%s\n",val4);
	b = printf("%s\n",val4);
	printf("%d %d \n", a ,b);
	a = ft_printf("%s\n",val5);
	b = printf("%s\n",val5);
	printf("%d %d \n", a ,b);
	a = ft_printf("%s\n",val6);
	b = printf("%s\n",val6);
	printf("%d %d \n", a ,b);
}
*/
int
	main(void)
{
	int	r;
    int v;

    v = 0;
	r = 0;
    r = ft_printf("Simple test\n");
    v = printf("Simple test\n");
    printf("%d %d \n", r ,v);
	r = ft_printf("");
    v = printf("");
    printf("%d %d \n", r ,v);
    ft_printf("--Format---");
	r = ft_printf("\n");
    v = printf("\n");
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", 0);
    v = printf("%d\n", 0);
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", 42);
    v = printf("%d\n", 42);
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", 1);
    v = printf("%d\n", 1);
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", 5454);
    v = printf("%d\n", 5454);
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", (int)2147483647);
    v = printf("%d\n", (int)2147483647);
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", (int)2147483648);
    v = printf("%d\n", (int)2147483648);
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", (int)-2147483648);
    v = printf("%d\n", (int)-2147483648);
    printf("%d %d \n", r ,v);
	r = ft_printf("%d\n", (int)-2147483649);
    v = printf("%d\n", (int)-2147483649);
    printf("%d %d \n", r ,v);
	ft_printf("\n");
	r = ft_printf("%x\n", 0);
    v = printf("%x\n", 0);
    printf("%d %d \n", r ,v);
	r = ft_printf("%x\n", 42);
    v = printf("%x\n", 42);
    printf("%d %d \n", r ,v);
	r = ft_printf("%x\n", 1);
    v = printf("%x\n", 1);
    printf("%d %d \n", r ,v);
	r = ft_printf("%x\n", 5454);
    v = printf("%x\n", 5454);
    printf("%d %d \n", r ,v);
	r = ft_printf("%x\n", (int)2147483647);
    v = printf("%x\n", (int)2147483647);
    printf("%d %d \n", r ,v);
	r = ft_printf("%x\n", (int)2147483648);
    v = printf("%x\n", (int)2147483648);
    printf("%d %d \n", r ,v);
	r = ft_printf("%x\n", (int)-2147483648);
    v = printf("%x\n", (int)-2147483648);
    printf("%d %d \n", r ,v);
	r = ft_printf("%x\n", (int)-2147483649);
    v = printf("%x\n", (int)-2147483649);
    printf("%d %d \n", r ,v);
    printf("\n");
	r = ft_printf("%s\n", "");
    v = printf("%s\n", "");
    printf("%d %d \n", r ,v);
	r = ft_printf("%s\n", "toto");
    v = printf("%s\n", "toto");
    printf("%d %d \n", r ,v);
	r = ft_printf("%s\n", "wiurwuyrhwrywuier");
    v = printf("%s\n", "wiurwuyrhwrywuier");
    printf("%d %d \n", r ,v);
	r = ft_printf("%s\n", NULL);
    v = printf("%s\n", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    v = printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    printf("%d %d \n", r ,v);
	ft_printf("\n--Mixed---\n");
	r = ft_printf("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    v = printf("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    printf("%d %d \n", r ,v);
	r = ft_printf("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    v = printf("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    printf("%d %d \n", r ,v);
	ft_printf("\n");
	r = ft_printf("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    v = printf("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    v = printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    printf("%d %d \n", r ,v);
	ft_printf("--1 Flag--\n");
	r = ft_printf("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	ft_printf("--2 Flags--\n");
	r = ft_printf("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	ft_printf("--Precision--\n");
	r = ft_printf("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	ft_printf("--Width--\n");
	r = ft_printf("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	ft_printf("--Width and Precision--\n");
	r = ft_printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    v = printf("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    printf("%d %d \n", r ,v);
	r = ft_printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	r = ft_printf("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    v = printf("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    printf("%d %d \n", r ,v);
	printf("written: %d\n", r);
}