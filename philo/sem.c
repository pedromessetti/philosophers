/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:35:05 by pedro             #+#    #+#             */
/*   Updated: 2023/08/14 10:40:56 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sem_init(t_semaphore *sem)
{
	sem->available = 1;
	pthread_mutex_init(&sem->mutex, NULL);
	return (0);
}

static int are_forks_available(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (!philo->r_fork->available)
	{
		pthread_mutex_unlock(&philo->r_fork->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->l_fork->mutex);
	if (!philo->l_fork->available)
	{
		pthread_mutex_unlock(&philo->l_fork->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->l_fork->mutex);
	return (1);
}

int	ft_sem_post(t_philo *philo)
{
	while (!are_forks_available(philo));
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->available = 0;
	printf("%dms philo %d has taken his right fork\n", get_time()
		- philo->data->init_time, philo->id);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->available = 0;
	printf("%dms philo %d has taken his left fork\n", get_time()
		- philo->data->init_time, philo->id);
	pthread_mutex_lock(&philo->state);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	philo->time_to_die = get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->state);
	start_eating(philo);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->available = 1;
	printf("%dms philo %d has dropped his left fork\n", get_time()
		- philo->data->init_time, philo->id);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->available = 1;
	printf("%dms philo %d has dropped his right fork\n", get_time()
		- philo->data->init_time, philo->id);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	start_sleeping(philo);
	return (0);
}

int	ft_sem_destroy(t_semaphore *sem)
{
	pthread_mutex_destroy(&sem->mutex);
	// free(sem);
	return (0);
}