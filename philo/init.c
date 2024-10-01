/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:35 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/30 11:36:39 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_initlaze_table(t_table *table, char **av, int flag)
{
	if (ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1
		|| ft_atoi(av[4]) == -1 || (av[5] && ft_atoi(av[5]) == -1))
		return ;
	table->nb_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (flag)
		table->nb_of_meals = ft_atoi(av[5]);
	else
		table->nb_of_meals = -2;
	table->time_to_start = 0;
	table->stop = 0;
	table->number_philos_ate = 0;
}

int	init_mutexes(t_table *table, t_mutex *mutexes)
{
	int		i;

	i = 0;
	while (i < table->nb_of_philo)
	{
		if (pthread_mutex_init(&mutexes[i].mutex, NULL))
			return (1);
		i++;
	}
	table->m1 = malloc(sizeof(pthread_mutex_t));
	table->m2 = malloc(sizeof(pthread_mutex_t));
	table->m_last_time = malloc(sizeof(pthread_mutex_t));
	table->meals_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->m1 || !table->m2 || !table->m_last_time || !table->meals_mutex)
		return (1);
	if (pthread_mutex_init(table->m1, NULL) || pthread_mutex_init(table->m2, NULL)
		|| pthread_mutex_init(table->m_last_time, NULL) || pthread_mutex_init(table->meals_mutex, NULL))
		return (1);
	return (0);
}

void	init_philo(t_table *table, t_philo *philo, t_mutex *mutexes)
{
	int		i;

	i = 0;
	while (i < table->nb_of_philo) 
	{
		philo[i].philo_id = i + 1;
		philo[i].number_of_meals = 0;
		philo[i].last_time_eat = ft_gettime();
		if (i % 2)
		{
			philo[i].left_fork = &mutexes[i].mutex;
			philo[i].right_fork = &mutexes[(i + 1) % table->nb_of_philo].mutex;
		}
		else
		{
			philo[i].left_fork = &mutexes[(i + 1) % table->nb_of_philo].mutex;
			philo[i].right_fork = &mutexes[i].mutex;
		}
		philo[i].table = table;
		i++;
	}
}
