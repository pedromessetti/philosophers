/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:03:57 by pedro             #+#    #+#             */
/*   Updated: 2024/03/02 20:35:51 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

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

	if (is_dead(philo))
		return (1);
	start_time = get_time();
	eating_time = philo->data->time_to_eat;
	pthread_mutex_lock(&philo->data->write);
	printf("%dms philo %d is eating\n", get_time() - philo->data->init_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->write);
	while ((get_time() - start_time) < eating_time)
	{
		if (is_dead(philo))
			return (1);
		usleep(1);
	}
	pthread_mutex_lock(&philo->state);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->state);
	if (is_dead(philo))
		return (1);
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
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

int	exec_routine(t_philo *philo)
{
	while (!are_forks_available(philo))
	{
		if (is_dead(philo))
			return (1);
	}
	grab_forks(philo);
	pthread_mutex_lock(&philo->state);
	philo->time_to_die = get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->state);
	if (start_eating(philo))
		return (1);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->available = 1;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->available = 1;
	pthread_mutex_unlock(&philo->r_fork->mutex);
	if (start_sleeping(philo))
		return (1);
	return (0);
}
