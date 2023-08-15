/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:03:57 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 16:19:51 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_sleeping(t_philo *philo)
{
	int	start_time;
	int	sleeping_time;

	if (is_dead(philo))
		return (1);
	start_time = get_time();
	sleeping_time = philo->data->time_to_sleep;
	pthread_mutex_lock(&philo->data->write);
	printf("%dms philo %d is sleeping\n", get_time() - philo->data->init_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->write);
	while ((get_time() - start_time) < sleeping_time)
	{
		if (is_dead(philo))
			return (1);
		usleep(1);
	}
	if (is_dead(philo))
		return (1);
	return (0);
}

int	start_eating(t_philo *philo)
{
	int	start_time;
	int	eating_time;

	start_time = get_time();
	eating_time = philo->data->time_to_eat;
	pthread_mutex_lock(&philo->data->write);
	printf("%dms philo %d is eating\n", get_time() - philo->data->init_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_lock(&philo->state);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->state);
	while ((get_time() - start_time) < eating_time)
	{
		if (is_dead(philo))
			return (1);
		usleep(1);
	}
	pthread_mutex_lock(&philo->state);
	philo->meals_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->state);
	return (0);
}

void	grab_forks(t_philo *philo)
{
	philo->r_fork->available = 0;
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%dms philo %d has taken his right fork\n", get_time()
			- philo->data->init_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	pthread_mutex_unlock(&philo->r_fork->mutex);
	philo->l_fork->available = 0;
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%dms philo %d has taken his left fork\n", get_time()
			- philo->data->init_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
}
