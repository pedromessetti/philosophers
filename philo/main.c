/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:24 by pedro             #+#    #+#             */
/*   Updated: 2023/08/08 07:01:38 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_sleeping(t_philo *philo)
{
	int	start_time;
	int	sleeping_time;

	start_time = get_time();
	sleeping_time = philo->data->time_to_sleep;
	printf("%dms philo %d is sleeping\n", get_time() - philo->data->init_time, philo->id);
	while ((get_time() - start_time) < sleeping_time)
		usleep(sleeping_time / 10);
}

void	start_eating(t_philo *philo)
{
	int	start_time;
	int	eating_time;

	start_time = get_time();
	eating_time = philo->data->time_to_eat;
	printf("%dms philo %d is eating\n", get_time() - philo->data->init_time, philo->id);
	philo->eating = 1;
	philo->meals_count++;
	while ((get_time() - start_time) < eating_time)
		usleep(eating_time / 10);
	philo->eating = 0;
}

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	pthread_mutex_lock(&philo->data->write);
	printf("data: %d", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->number_of_philos)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			printf("%dms philo %d died\n", get_time() - philo->data->init_time, philo->id);
		if (philo->meals_count == philo->data->number_of_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->meals_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (pthread_create(&philo->thread, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		ft_sem_post(philo);
		printf("%dms philo %d is thinking\n", get_time() - philo->data->init_time, philo->id);
	}
	return ((void *)0);
}

void	start_dinner(t_data *data)
{
	int	i;

	i = -1;
	data->init_time = get_time();
	while (++i < data->number_of_philos)
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(data->philos[i].thread, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_ac(ac))
		return (1);
	if (check_av(av) == -1)
		return (1);
	if (init(av, &data))
		return (1);
	start_dinner(&data);
	return (0);
}
