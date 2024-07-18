

#include "philo.h"

void ft_usleep(size_t time)
{
    size_t newtime;
    newtime = ft_gettime();
    while (ft_gettime()- newtime < time);
}

void    ft_eating(t_philo *philo, t_table *table)
{
        pthread_mutex_lock(philo->right_fork);
        printf("%zu %d has taken a fork\n", (ft_gettime() - table->start_at), philo->philo_id);
        pthread_mutex_lock(philo->left_fork);
        philo->last_meal = ft_gettime();
        printf("%zu %d has taken a fork\n", (ft_gettime() - table->start_at), philo->philo_id);
        printf("%zu %d is eating\n", (ft_gettime() - table->start_at), philo->philo_id);
        ft_usleep(table->time_to_eat);//
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        printf("%zu %d is sleeping\n", (ft_gettime() - table->start_at), philo->philo_id);
        ft_usleep(table->time_to_sleep);
        printf("%zu %d is thinking\n", (ft_gettime() - table->start_at), philo->philo_id);
}


void    *routine(void *philos)
{
    t_philo *philo = (t_philo *) philos;
    t_table *table = philo->table;
    while (1)
    {
        ft_eating(philo, table);
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

    return (0);
}

void    ft_monitor(t_table *table, t_philo *philo)
{
    size_t i;
    size_t time;
    while (1)
    {
        i = 0;
        // if (philo->philo_id % 2 != 0)
        //     usleep(500);
        while (i < table->nb_of_philo)
        {
            time = ft_gettime();
            if (time - philo[i].last_meal > table->time_to_die)
            {
                printf("%zu %d died\n", (time - table->start_at), philo[i].philo_id);
                exit (0);
            }
            i++;
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



