/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:40 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/30 11:36:44 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->table->m1);
	if (philo->table->stop) {
		pthread_mutex_unlock(philo->table->m1);
		return (1);
	}
	pthread_mutex_unlock(philo->table->m1);
	pthread_mutex_lock(philo->left_fork);
	ft_print_take_fork(philo, 0);
	if (check_for_one(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	ft_print_take_fork(philo, 1);
	pthread_mutex_lock(philo->table->m_last_time);
	philo->last_time_eat = ft_gettime();
	pthread_mutex_unlock(philo->table->m_last_time);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(philo->table->m_last_time);
	if (philo->number_of_meals < philo->table->nb_of_meals)
		philo->number_of_meals++;
	pthread_mutex_unlock(philo->table->m_last_time);
	if (check_meals(philo))
		return (1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->table->m1);
	if (philo->table->stop) {
		pthread_mutex_unlock(philo->table->m1);
		return (1);
	}
	pthread_mutex_unlock(philo->table->m1);
	time = ft_gettime() - philo->table->time_to_start;
	pthread_mutex_lock(philo->table->m2);
	printf("%ld  %d is sleeping\n", time, philo->philo_id);
	pthread_mutex_unlock(philo->table->m2);
	ft_usleep(philo->table->time_to_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->table->m1);
	if (philo->table->stop)
	{
		pthread_mutex_unlock(philo->table->m1);
		return (1);
	}
	pthread_mutex_unlock(philo->table->m1);
	time = ft_gettime() - philo->table->time_to_start;
	pthread_mutex_lock(philo->table->m2);
	printf("%ld  %d is thinking\n", time, philo->philo_id);
	pthread_mutex_unlock(philo->table->m2);
	return (0);
}

void	*routine(void *my_philo)
{
	t_philo		*philo;

	philo = (t_philo *)my_philo;
	if (philo->philo_id % 2 == 0)
		usleep(250);
	while (!philo->table->stop)
	{
		if (ft_eat(philo) || ft_sleep(philo) || ft_think(philo))
			break ;
		usleep(400);
	}
	return (NULL);
}
