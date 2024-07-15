

#include "philo.h"

void    *routine(void *philos)
{
    t_philo *philo = (t_philo *) philos;
    t_table *table = philo->table;
    while (1)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%zu ms, %d token left fork\n", (ft_gettime() - table->start_at), philo->philo_id);
        pthread_mutex_lock(philo->right_fork);
        printf("%zu ms, %d token right fork\n", (ft_gettime() - table->start_at), philo->philo_id);
        printf("%zu ms, %d is eating\n", (ft_gettime() - table->start_at), philo->philo_id);
        philo->last_meal = ft_gettime();
        usleep(table->time_to_eat * 1000);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        printf("%zu ms, %d is sleeping\n", (ft_gettime() - table->start_at), philo->philo_id);
        usleep(table->time_to_sleep * 1000);
        printf("%zu ms, %d is thinking\n", (ft_gettime() - table->start_at), philo->philo_id);

    }
    return (0);
}

int     init_philo(t_table *table, t_philo *philo)
{
    size_t     i;

    i = -1;
    while (++i < table->nb_of_philo)
    {
        philo[i].table = table;
        philo[i].philo_id = i + 1;
        philo[i].meals_counter = 0;
        philo[i].if_full = 0;
        philo[i].last_meal = ft_gettime();
        philo[i].left_fork = &table->forks[i];
        if (i + 1 == table->nb_of_philo)
            philo[i].right_fork = &table->forks[0];
        else
            philo[i].right_fork = &table->forks[i + 1];
    }

    // i = -1;
    // while (++i < table->nb_of_philo)
    // {
    //     printf("--->%d\n", philo[i].meals_counter);
    //     printf("--->%d\n", philo[i].if_full);
    //     printf("--->%zu\n", philo[i].last_meal);
    //     printf("=======================================\n");
    // }
    return (0);
}

void    ft_monitor(t_table *table, t_philo *philo)
{
    size_t i = 0;
    while (1)
    {
        while (i < table->nb_of_philo)
        {
            if (ft_gettime() - philo[i].last_meal < table->time_to_die)
            {
                printf("%zu ms, %d is die\n", (ft_gettime() - table->start_at), philo[i].philo_id);
                exit (0);
            }
        }
    }
}

void    create_pthreads(t_table *table)
{
    size_t     i;
    t_philo *philo;

    i = -1;
    philo = malloc(sizeof(t_philo) * table->nb_of_philo);
    if (!philo)
        return ;
    init_philo(table, philo);
    while(++i < table->nb_of_philo)
    {
        pthread_create(&philo[i].philo, NULL, &routine, &philo[i]);
        usleep(20);
    }
    ft_monitor(table, philo);
    i = -1;
    while (++i < table->nb_of_philo)
        pthread_join(philo[i].philo, NULL);
}



