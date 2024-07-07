

#include "philo.h"

int     init_philo(t_table *table)
{
    int     i;
    t_philo *philo;

    i = -1;
    philo = malloc(sizeof(pthread_t) * table->nb_of_philo);
    if (!philo)
        return (NULL);
    // while (++i < table->nb_of_philo)
    // {
    //     philo[i].philo_id = i;
    //     philo[i].left_fork = &table->forks[i];
    //     philo[i].right_fork = 0;
    //     philo[i].philo = 
    // }
}