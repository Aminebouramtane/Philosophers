/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:05 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/30 11:36:08 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_take_fork(t_philo *philo, int flag)
{
	long	time;

	time = ft_gettime() - philo->table->time_to_start;
	pthread_mutex_lock(philo->table->m2);
	pthread_mutex_lock(philo->table->m1);
	if (philo->table->stop)
	{
		pthread_mutex_unlock(philo->table->m1);
		pthread_mutex_unlock(philo->table->m2);
		return ;
	}
	pthread_mutex_unlock(philo->table->m1);
	if (flag)
	{
		printf("%ld  %d has taken a fork\n", time, philo->philo_id);
		printf("%ld  %d is eating\n", time, philo->philo_id);
	}
	else
		printf("%ld  %d has taken a fork\n", time, philo->philo_id);
	pthread_mutex_unlock(philo->table->m2);
}
