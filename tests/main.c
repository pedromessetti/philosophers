/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:24 by pedro             #+#    #+#             */
/*   Updated: 2023/08/03 17:06:40 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(int philo)
{
	printf("Philosopher %d is eating\n", philo + 1);
}

void	*routine(void *n)
{
	t_semaphore	*forks;
	int			philo;

	philo = *(int *)n;
	forks = (t_semaphore *)((void **)n)[1];
	printf("Philosopher %d want to eat\n", philo + 1);
	printf("Philosopher %d tries to pick left fork\n", philo + 1);
	ft_sem_wait(&forks[philo]);
	printf("Philosopher %d picked left fork\n", philo + 1);
	printf("Philosopher %d tries to pick right fork\n", philo + 1);
	ft_sem_wait(&forks[(philo + 1) % 5]);
	printf("Philosopher %d picked right fork\n", philo + 1);
	eat(philo);
	sleep(2);
	printf("Philosopher %d finished eating\n", philo + 1);
	ft_sem_post(&forks[(philo + 1) % 5]);
	printf("Philosopher %d released right fork\n", philo + 1);
	ft_sem_post(&forks[philo]);
	printf("Philosopher %d released left fork\n", philo + 1);
	return (NULL);
}

void	start_program(t_philo *philo_table, t_semaphore *forks)
{
	pthread_t	threads[philo_table->number_of_philos];
	int			i;
	void		*n[philo_table->number_of_philos][2];

	i = -1;
	while (++i < philo_table->number_of_philos)
	{
		ft_sem_init(&forks[i], 1);
		n[i][0] = malloc(sizeof(int));
		*(int *)n[i][0] = i;
		n[i][1] = &forks;
		pthread_create(&threads[i], NULL, routine, &n[i]);
	}
	i = -1;
	while (++i < philo_table->number_of_philos) {
		pthread_join(threads[i], NULL);
		free(n[i][0]);
	}
}

t_philo	set_philos_table(char **av, t_philo *philos_table)
{
	philos_table->number_of_philos = ft_atoi(av[1]);
	philos_table->time_to_die = ft_atoi(av[2]);
	philos_table->time_to_eat = ft_atoi(av[3]);
	philos_table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos_table->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		philos_table->number_of_times_each_philosopher_must_eat = -1;
	return (*philos_table);
}

int	main(int ac, char **av)
{
	t_philo		philos_table;
	t_semaphore	*forks;

	check_ac(ac);
	if (check_av(av) == -1)
		return (1);
	else
	{
		philos_table = set_philos_table(av, &philos_table);
		if (philos_table.number_of_philos < 1)
			return (1);
	}
	forks = malloc(sizeof(t_semaphore) * philos_table.number_of_philos);
	printf("Number of philosophers: %d\n", philos_table.number_of_philos);
	start_program(&philos_table, forks);
	free(forks);
	return (0);
}
