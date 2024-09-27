
#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval t_time;

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
	int				number_philos_ate;
	pthread_t *threads;
    pthread_t monitor;
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

typedef struct my_mutex
{
	pthread_mutex_t	mutex;
}					t_mutex;


int ft_atoi(char *in);

#endif