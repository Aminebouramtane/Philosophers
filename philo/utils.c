

#include "philo.h"

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
		i++;
    }
}

int ft_atoi(char *in)
{
    int     res;
    int     i;

	i = 0;
	res= 0;
    while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
        i++;
    if (in[i] == '+' || in[i] == '-')
    {
        if (in[i] == '-')
        {
			ft_putstr("[ERROR] give me positive numbers ...");
			exit(1);
		}
		i++;
    }
    while (in[i])
	{
		res = res * 10 + (in[i] - '0');
		if (res > 2147483647)
			ft_putstr("[ERROR] Number to big ...");
		i++;
	}
	return(res);
}