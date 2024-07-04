
#include "philo.h"

size_t     ft_gettime(void)
{
    t_time  time;
    
    gettimeofday(&time, NULL);
    return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


void    ft_initlaze_table(t_table *table, char **av)
{
    table->nb_of_philo = atoi(av[1]);
    table->time_to_die = atoi(av[3]);
    table->time_to_eat = atoi(av[2]);
    table->time_to_sleep = atoi(av[4]);
    if (table->five_args)
        table->nb_of_meals = atoi(av[5]);
    table->start_at = ft_gettime();
}

void    ft_init(int ac, char **av)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return ;
    if (ac == 6)
        table->five_args = 1;
    ft_initlaze_table(table, av);
}

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        ft_init(ac, av);
        ft_putstr("enter\n");
    }
}
    // printf("%zu\n", table->nb_of_philo);
    // printf("%zu\n", table->time_to_die);
    // printf("%zu\n", table->time_to_eat);
    // printf("%zu\n", table->time_to_sleep);
    // printf("%d\n", table->five_args);
    // printf("->>>>>>>>>>>>%zu\n", table->start_at);