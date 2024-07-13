

#ifndef PHILO_H
 #define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef pthread_mutex_t t_mutex;

typedef struct timeval t_time;

typedef struct s_philo
{
    int         philo_id;
    pthread_t   philo;
    int         meals_counter;
    int         if_full;
    int			philo_number;
    size_t      last_meal;
    t_mutex     *left_fork;
    t_mutex     *right_fork;
}       t_philo;

typedef struct s_table
{
    size_t      nb_of_philo;
    size_t      time_to_die;
    size_t      time_to_eat;
    size_t      time_to_sleep;
    size_t      nb_of_meals;
    size_t      start_at;
    int         die_or_full;
    int         five_args;
    t_mutex     *forks;
    t_philo     *philo;
}       t_table;

void    ft_putstr(char *str);
int     ft_atoi(char *in);
void    create_pthreads(t_table *table);


#endif