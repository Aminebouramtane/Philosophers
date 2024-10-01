/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:17 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/30 11:40:34 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_gettime(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(long time)
{
	long	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < (size_t)time)
		usleep(500);
	return (0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_atoi(char *in)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (in[i] == 32 || (in[i] >= 9 && in[i] <= 13))
		i++;
	if (in[i] == '+' || in[i] == '-')
	{
		if (in[i] == '-')
		{
			ft_putstr("[ERROR] give me positive numbers ...");
			return (-1);
		}
		i++;
	}
	while (in[i])
	{
		if (in[i] >= '0' && in[i] <= '9')
			res = res * 10 + (in[i] - '0');
		else
		{
			ft_putstr("[ERROR] Not a number ...");
			return (-1);
		}
		if (res > 2147483647)
		{
			ft_putstr("[ERROR] Number to big ...");
			return (-1);
		}
		i++;
	}
	return (res);
}
