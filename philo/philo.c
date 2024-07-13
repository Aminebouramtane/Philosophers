

#include "philo.h"

void    *routine(void *str)
{
    (void)str;
    printf("hhhhhhh\n");
    return (0);
}

int     init_philo(t_table *table, t_philo *philo)
{
    size_t     i;

    i = -1;
    while (++i < table->nb_of_philo)
    {
        philo[i].philo_id = i;
        philo[i].meals_counter = 0;
        philo[i].if_full = 0;
        philo[i].last_meal = 0;
        philo[i].philo_number = i + 1;
        philo[i].left_fork = &table->forks[i];
        philo[i].right_fork = 0;
    }

    i = -1;
    while (++i < table->nb_of_philo)
    {
        printf("--->%d\n", philo[i].meals_counter);
        printf("--->%d\n", philo[i].if_full);
        printf("--->%zu\n", philo[i].last_meal);
        printf("--->%d\n", philo[i].philo_number);
        printf("=======================================\n");
    }
    return (0);
}

void    create_pthreads(t_table *table)
{
    size_t     i;
    t_philo *philo;

    i = -1;
    philo = malloc(sizeof(t_philo) * table->nb_of_philo);
    if (!philo)
        return ;
    while(++i < table->nb_of_philo)
        pthread_create(&philo[i].philo, NULL, &routine, NULL);
    i = -1;
    while (++i < table->nb_of_philo)
        pthread_join(philo[i].philo, NULL);
    init_philo(table, philo);
}



