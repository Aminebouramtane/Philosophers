
#include "philo.h"

size_t     ft_gettime(void)
{
    t_time  time;
    
    gettimeofday(&time, NULL);
    return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


void    ft_initlaze_table(t_table *table, char **av)
{
    if (ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1
    || ft_atoi(av[4]) == -1 || (av[5] && ft_atoi(av[5]) == -1))
        return ;
    table->nb_of_philo = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]);
    table->time_to_eat = ft_atoi(av[3]);
    table->time_to_sleep = ft_atoi(av[4]);
    if (table->five_args)
        table->nb_of_meals = ft_atoi(av[5]);
    else
        table->nb_of_meals = -2;
    table->start_at = ft_gettime();
    table->flag = 1;
}

int 	intial_mutex(t_table *table)
{
    size_t     i;

    i = -1;
	table->forks = malloc(sizeof(t_mutex) * table->nb_of_philo);
    if (!table->forks)
        return (0);
    table->flag_mutex = malloc(sizeof(t_mutex));
    if (!table->flag)
        return 0;
    pthread_mutex_init(table->flag_mutex, NULL);
    while (++i < table->nb_of_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) == -1)
            return (0);
    }
    return (1);
}

void    ft_init(int ac, char **av)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return ;
    table->five_args = 0;
    if (ac == 6)
        table->five_args = 1;
    ft_initlaze_table(table, av);
    if (!intial_mutex(table))
    {
        ft_putstr("[ERROR] initile mutex ...");
        exit(1);
    }
    create_pthreads(table);
}

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        ft_init(ac, av);
    }
}

// printf("%zu\n", table->nb_of_philo);
// printf("%zu\n", table->time_to_die);
// printf("%zu\n", table->time_to_eat);
// printf("%zu\n", table->time_to_sleep);
// printf("%d\n", table->five_args);
// printf("->>>>>>>>>>>>%zu\n", table->start_at);