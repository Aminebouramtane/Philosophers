/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:10 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/30 11:43:23 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval	t_time;

typedef struct s_table
{
	long			nb_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_meals;
	long			time_to_start;
	int				stop;
	pthread_mutex_t	*m1;
	pthread_mutex_t	*m2;
	pthread_mutex_t	*m_last_time;
	pthread_mutex_t	*meals_mutex;
	int				number_philos_ate;
	pthread_t		*threads;
	pthread_t		monitor;
}					t_table;

typedef struct s_philo
{
	pthread_t		philo;
	int				philo_id;
	int				number_of_meals;
	long			last_time_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}					t_philo;

typedef	struct my_mutex
{
	pthread_mutex_t	mutex;
}					t_mutex;

int		ft_atoi(char *in);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);
void	*routine(void *my_philo);
void	ft_print_take_fork(t_philo *philo, int flag);
void	*ft_monitor(void *philos);
void	ft_initlaze_table(t_table *table, char **av, int flag);
int		init_mutexes(t_table *table, t_mutex *mutexes);
void	init_philo(t_table *table, t_philo *philo, t_mutex *mutexes);
size_t	ft_gettime(void);
int		ft_usleep(long time);
int		check_meals(t_philo *philo);
int		check_for_one(t_philo *philo);
void	ft_join(t_table *table, t_mutex *mutexes, t_philo *philo);

#endif