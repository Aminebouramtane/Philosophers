#include "philo.h"

size_t ft_gettime(void)
{
    t_time time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int ft_usleep(long time)
{
    long start = ft_gettime();
    while ((ft_gettime() - start) < (size_t)time)
        usleep(500);
    return (0);
}

void ft_initlaze_table(t_table *table, char **av, int flag)
{
    if (ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1
        || ft_atoi(av[4]) == -1 || (av[5] && ft_atoi(av[5]) == -1))
        return;
    table->nb_of_philo = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]);
    table->time_to_eat = ft_atoi(av[3]);
    table->time_to_sleep = ft_atoi(av[4]);
	if (flag)
		table->nb_of_meals = ft_atoi(av[5]);
	else
		table->nb_of_meals = -2;
    table->time_to_start = 0;
    table->stop = 0;
    table->number_philos_ate = 0;
}

int init_mutexes(t_table *table, t_mutex *mutexes)
{
    int i;

	i = 0;
    while (i < table->nb_of_philo)
	{
        if (pthread_mutex_init(&mutexes[i].mutex, NULL))
            return (1);
        i++;
    }

    table->m1 = malloc(sizeof(pthread_mutex_t));
    table->m2 = malloc(sizeof(pthread_mutex_t));
    table->m_last_time = malloc(sizeof(pthread_mutex_t));
    if (!table->m1 || !table->m2 || !table->m_last_time)
        return (1);
    if (pthread_mutex_init(table->m1, NULL) || pthread_mutex_init(table->m2, NULL)
        || pthread_mutex_init(table->m_last_time, NULL))
        return (1);
    return (0);
}

void init_philo(t_table *table, t_philo *philo, t_mutex *mutexes)
{
    int i = 0;

    while (i < table->nb_of_philo) {
        philo[i].philo_id = i + 1;
        philo[i].number_of_meals = 0;
        philo[i].last_time_eat = ft_gettime();
        if (i % 2)
		{
            philo[i].left_fork = &mutexes[i].mutex;
            philo[i].right_fork = &mutexes[(i + 1) % table->nb_of_philo].mutex;
        }
		else
		{
            philo[i].left_fork = &mutexes[(i + 1) % table->nb_of_philo].mutex;
            philo[i].right_fork = &mutexes[i].mutex;
        }
        philo[i].table = table;
        i++;
    }
}

int check_meals(t_philo *philo)
{
    pthread_mutex_lock(philo->table->m_last_time);
    int nb_of_meals = philo->table->nb_of_meals;
    pthread_mutex_unlock(philo->table->m_last_time);

    if (philo->number_of_meals == nb_of_meals)
	{
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_lock(philo->table->m_last_time);
        philo->table->number_philos_ate++;
        pthread_mutex_unlock(philo->table->m_last_time);
        return (1);
    }
    return (0);
}

void ft_print_take_fork(t_philo *philo, int flag)
{
    long time = ft_gettime() - philo->table->time_to_start;
    pthread_mutex_lock(philo->table->m2);
    pthread_mutex_lock(philo->table->m1);

    if (philo->table->stop) {
        pthread_mutex_unlock(philo->table->m1);
        pthread_mutex_unlock(philo->table->m2);
        return ;
    }
    pthread_mutex_unlock(philo->table->m1);
    if (flag)
	{
        printf("%ld  %d has taken a fork\n", time, philo->philo_id);
        printf("%ld  %d is eating\n", time, philo->philo_id);
    }
	else
        printf("%ld  %d has taken a fork\n", time, philo->philo_id);
    pthread_mutex_unlock(philo->table->m2);
}

int	check_for_one(t_philo *philo)
{
	int	end_simulation;

	if (philo->table->nb_of_philo == 1)
	{
		pthread_mutex_lock(philo->table->m1);
		end_simulation = philo->table->stop;
		pthread_mutex_unlock(philo->table->m1);
		while (end_simulation == 0)
		{
			pthread_mutex_lock(philo->table->m1);
			end_simulation = philo->table->stop;
			pthread_mutex_unlock(philo->table->m1);
		}
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int ft_eat(t_philo *philo)
{
    if (philo->table->stop)
        return (1);
    pthread_mutex_lock(philo->left_fork);
    ft_print_take_fork(philo, 0);
	if (check_for_one(philo) == 1)
		return (1);
    pthread_mutex_lock(philo->right_fork);
    ft_print_take_fork(philo, 1);
    pthread_mutex_lock(philo->table->m_last_time);
    philo->last_time_eat = ft_gettime();
    pthread_mutex_unlock(philo->table->m_last_time);
    ft_usleep(philo->table->time_to_eat);
    pthread_mutex_lock(philo->table->m_last_time);
    if (philo->number_of_meals < philo->table->nb_of_meals)
        philo->number_of_meals++;
    pthread_mutex_unlock(philo->table->m_last_time);
    if (check_meals(philo))
        return (1);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (0);
}

int ft_sleep(t_philo *philo)
{
	long time;

    if (philo->table->stop)
        return (1);
    time = ft_gettime() - philo->table->time_to_start;
    pthread_mutex_lock(philo->table->m2);
    pthread_mutex_lock(philo->table->m1);

    if (philo->table->stop)
	{
        pthread_mutex_unlock(philo->table->m1);
        pthread_mutex_unlock(philo->table->m2);
        return (1);
    }
    pthread_mutex_unlock(philo->table->m1);
    printf("%ld  %d is sleeping\n", time, philo->philo_id);
    pthread_mutex_unlock(philo->table->m2);
    ft_usleep(philo->table->time_to_sleep);
    return (0);
}

int ft_think(t_philo *philo)
{
    if (philo->table->stop)
        return (1);
    long time = ft_gettime() - philo->table->time_to_start;
    pthread_mutex_lock(philo->table->m2);
    pthread_mutex_lock(philo->table->m1);
    if (philo->table->stop) {
        pthread_mutex_unlock(philo->table->m1);
        pthread_mutex_unlock(philo->table->m2);
        return (1);
    }
    pthread_mutex_unlock(philo->table->m1);
    printf("%ld  %d is thinking\n", time, philo->philo_id);
    pthread_mutex_unlock(philo->table->m2);
    return (0);
}

void *routine(void *my_philo)
{
    t_philo *philo;
	
	philo = (t_philo *)my_philo;
    if (philo->philo_id % 2 == 0)
        usleep(250);
    while (!philo->table->stop)
    {
        if (ft_eat(philo) || ft_sleep(philo) || ft_think(philo))
            break ;
        usleep(400);
    }
    return (NULL);
}

void *ft_monitor(void *philos)
{
    t_philo *philo;
    int i;
    long time;

    philo = (t_philo *)philos;
    i = 0;
    while (!philo->table->stop)
    {
        pthread_mutex_lock(philo->table->m_last_time);
        time = ft_gettime() - philo[i].last_time_eat;
        if (time > philo->table->time_to_die)
        {
            pthread_mutex_lock(philo->table->m1);
            philo->table->stop = 1;
            printf("%ld  %d died\n", ft_gettime() - philo->table->time_to_start, philo[i].philo_id);
            pthread_mutex_unlock(philo->table->m1);
        }
        if (philo->table->number_philos_ate == philo->table->nb_of_philo)
        {
            pthread_mutex_lock(philo->table->m1);
            philo->table->stop = 1;
            pthread_mutex_unlock(philo->table->m1);
        }
        pthread_mutex_unlock(philo->table->m_last_time);
        i = (i + 1) % philo->table->nb_of_philo;
        usleep(1000);
    }
    return (NULL);
}

void    ft_join(t_table *table, t_mutex *mutexes, t_philo *philo)
{
    int     i;

    i = -1;
    while (++i < table->nb_of_philo)
        pthread_join(table->threads[i], NULL);
    pthread_join(table->monitor, NULL);
    i = -1;
    while (++i < table->nb_of_philo)
        pthread_mutex_destroy(&mutexes[i].mutex);
    pthread_mutex_destroy(table->m1);
    pthread_mutex_destroy(table->m2);
    pthread_mutex_destroy(table->m_last_time);
    free(table->m1);
    free(table->m2);
    free(table->m_last_time);
    free(table->threads);
    free(philo);
    free(mutexes);
}

int main(int ac, char **av)
{
    t_table table;
    t_philo *philo;
    t_mutex *mutexes;
    int i;

    i = -1;
    if (ac < 5 || ac > 6)
        return (1);

    ft_initlaze_table(&table, av, ac == 6);
    if (table.nb_of_philo < 1 || table.nb_of_philo > 200 || table.time_to_die < 60 ||
        table.time_to_eat < 60 || table.time_to_sleep < 60 || table.nb_of_meals == 0)
        return (1);
    table.threads = malloc(sizeof(pthread_t) * table.nb_of_philo);
    mutexes = malloc(sizeof(t_mutex) * table.nb_of_philo);
    philo = malloc(sizeof(t_philo) * table.nb_of_philo);
    if (!table.threads || !mutexes || !philo || init_mutexes(&table, mutexes))
        return (1);
    init_philo(&table, philo, mutexes);
    table.time_to_start = ft_gettime();
    while (++i < table.nb_of_philo)
        pthread_create(&table.threads[i], NULL, &routine, (void *)&philo[i]);
    pthread_create(&table.monitor, NULL, &ft_monitor, (void *)philo);
    i = -1;
    ft_join(&table, mutexes, philo);
    return (0);
}
