

#include "philo.h"

void    *routine(void)
{
    printf("hhhhhhh\n");
}

void    create_pthreads(t_table *table)
{
    int     i;
    t_philo *philo;

    i = -1;
    philo = malloc(sizeof(pthread_t) * table->nb_of_philo);
    if (!philo)
        return (NULL);
    while(++i < table->nb_of_philo)
        pthread_create(&philo[i].philo, NULL, &routine, NULL);
    i = -1;
    while (++i < table->nb_of_philo)
        pthread_join(&philo[i].philo, NULL);
}

int     init_philo(t_table *table)
{
    int     i;
    t_philo *philo;

    i = -1;
    while (++i < table->nb_of_philo)
    {
        philo[i].philo_id = i;
        philo[i].meals_counter = 0;
        philo[i].if_full = 0;
        philo[i].last_meal = 0;
        philo[i].left_fork = &table->forks[i];
        philo[i].right_fork = 0;
    }
}


