/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:24 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 09:36:05 by pedro            ###   ########.fr       */
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
	while ((get_time() - start_time) < sleeping_time) {
		if (is_dead(philo))
			return ;
		usleep(sleeping_time / 10);
	}
}

void	start_eating(t_philo *philo)
{
	int	start_time;
	int	eating_time;

	start_time = get_time();
	eating_time = philo->data->time_to_eat;
	printf("%dms philo %d is eating\n", get_time() - philo->data->init_time, philo->id);
	pthread_mutex_lock(&philo->state);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->state);
	while ((get_time() - start_time) < eating_time) {
		if (is_dead(philo))
			return ;
		usleep(eating_time / 10);
	}
	pthread_mutex_lock(&philo->state);
	philo->meals_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->state);
}

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->state);
		if (philo->data->finished >= philo->data->number_of_philos) {
			philo->data->dead = 1;
		}
		pthread_mutex_unlock(&philo->state);
	}
	return ((void *)0);
}

void	*supervisor(void *thread_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)thread_pointer;
	while (philo->data->dead == 0)
	{
		if (is_dead(philo))
			return ((void *)0);
		pthread_mutex_lock(&philo->state);
		if (philo->meals_count == philo->data->number_of_meals) {
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->state);
	}
	return ((void *)0);
}

void	*routine(void *thread_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)thread_pointer;
	philo->time_to_die = philo->data->time_to_die + get_time();
	//if (pthread_create(&philo->thread, NULL, &supervisor, (void *)philo))
	//	return ((void *)1);
	while (philo->data->dead == 0)
	{
		if(is_dead(philo))
			break;
		if(ft_sem_post(philo))
			break;
		if (philo->meals_count == philo->data->number_of_meals)
			break;
		if (is_dead(philo))
			break;
		printf("%dms philo %d is thinking\n", get_time() - philo->data->init_time, philo->id);
	}
	//if (pthread_join(philo->thread, NULL))
	//	return ((void *)1);
	return ((void *)0);
}

void	start_simulation(t_data *data)
{
	int	i;
	pthread_t	monitor_thread;

	i = -1;
	data->init_time = get_time();
	//monitor should check for the dead status & if all have eaten
	if (data->number_of_meals > 0)
		pthread_create(&monitor_thread, NULL, &monitor, &data->philos[0]);
	while (++i < data->number_of_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		usleep(1 / 10);
	}
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
	start_simulation(&data);
	end_simulation(&data);
	return (0);
}
