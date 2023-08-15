/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:35:05 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 17:12:40 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sem_init(t_semaphore *sem)
{
	sem->available = 1;
	pthread_mutex_init(&sem->mutex, NULL);
	return (0);
}

int	ft_sem_post(t_philo *philo)
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
	if (is_dead(philo))
		return (1);
	start_eating(philo);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->available = 1;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->available = 1;
	pthread_mutex_unlock(&philo->r_fork->mutex);
	if (start_sleeping(philo))
		return (1);
	usleep(10);
	return (0);
}

int	ft_sem_destroy(t_semaphore *sem)
{
	pthread_mutex_destroy(&sem->mutex);
	return (0);
}
