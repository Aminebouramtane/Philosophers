/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:29 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/30 11:38:25 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *philo)
{
	int		nb_of_meals;

	pthread_mutex_lock(philo->table->meals_mutex);
	pthread_mutex_lock(philo->table->m_last_time);
	nb_of_meals = philo->table->nb_of_meals;
	pthread_mutex_unlock(philo->table->m_last_time);
	if (philo->number_of_meals == nb_of_meals)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(philo->table->m_last_time);
		philo->table->number_philos_ate++;
		pthread_mutex_unlock(philo->table->m_last_time);
		pthread_mutex_unlock(philo->table->meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->table->meals_mutex);
	return (0);
}

int	check_for_one(t_philo *philo)
{
	int		end_simulation;

	if (philo->table->nb_of_philo == 1)
	{
		pthread_mutex_lock(philo->table->m1);
		end_simulation = philo->table->stop;
		pthread_mutex_unlock(philo->table->m1);
		while (end_simulation == 0)
		{
			pthread_mutex_lock(philo->table->m1);
			end_simulation = philo->table->stop;
			pthread_mutex_unlock(philo->table->m1);
		}
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	ft_join(t_table *table, t_mutex *mutexes, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < table->nb_of_philo)
		pthread_join(table->threads[i], NULL);
	pthread_join(table->monitor, NULL);
	i = -1;
	while (++i < table->nb_of_philo)
		pthread_mutex_destroy(&mutexes[i].mutex);
	pthread_mutex_destroy(table->m1);
	pthread_mutex_destroy(table->m2);
	pthread_mutex_destroy(table->m_last_time);
	free(table->m1);
	free(table->m2);
	free(table->m_last_time);
	free(table->threads);
	free(table->meals_mutex);
	free(philo);
	free(mutexes);
}

int	main(int ac, char **av)
{
	t_table		table;
	t_philo		*philo;
	t_mutex		*mutexes;
	int			i;

	i = -1;
	if (ac < 5 || ac > 6)
		return (1);
	ft_initlaze_table(&table, av, ac == 6);
	if (table.nb_of_philo < 1 || table.nb_of_philo > 200
		|| table.time_to_die < 60 || table.time_to_eat < 60
		|| table.time_to_sleep < 60 || table.nb_of_meals == 0)
		return (1);
	table.threads = malloc(sizeof(pthread_t) * table.nb_of_philo);
	mutexes = malloc(sizeof(t_mutex) * table.nb_of_philo);
	philo = malloc(sizeof(t_philo) * table.nb_of_philo);
	if (!table.threads || !mutexes || !philo || init_mutexes(&table, mutexes))
		return (1);
	init_philo(&table, philo, mutexes);
	table.time_to_start = ft_gettime();
	while (++i < table.nb_of_philo)
		pthread_create(&table.threads[i], NULL, &routine, (void *)&philo[i]);
	pthread_create(&table.monitor, NULL, &ft_monitor, (void *)philo);
	ft_join(&table, mutexes, philo);
	return (0);
}
