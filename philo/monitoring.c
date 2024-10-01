/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:23 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/30 11:39:04 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *philos)
{
	t_philo	*philo;
	int		i;
	long	time;

	philo = (t_philo *)philos;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(philo->table->meals_mutex);
		pthread_mutex_lock(philo->table->m_last_time);
		time = ft_gettime() - philo[i].last_time_eat;
		pthread_mutex_unlock(philo->table->m_last_time);
		pthread_mutex_lock(philo->table->m1);
		if (philo->table->stop || time > philo->table->time_to_die)
		{
			philo->table->stop = 1;
			printf("%ld  %d died\n", ft_gettime() - \
			philo->table->time_to_start, philo[i].philo_id);
			pthread_mutex_unlock(philo->table->m1);
			pthread_mutex_unlock(philo->table->meals_mutex);
			break ;
		}
		if (philo->table->number_philos_ate == philo->table->nb_of_philo)
		{
			philo->table->stop = 1;
			pthread_mutex_unlock(philo->table->m1);
			pthread_mutex_unlock(philo->table->meals_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->table->m1);
		pthread_mutex_unlock(philo->table->meals_mutex);
		i = (i + 1) % philo->table->nb_of_philo;
		usleep(500);
	}
	return (NULL);
}
