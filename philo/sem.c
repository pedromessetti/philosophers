/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:35:05 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 09:35:29 by pedro            ###   ########.fr       */
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
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork->mutex);
		if (!philo->r_fork->available)
		{
			pthread_mutex_unlock(&philo->r_fork->mutex);
			return (0);
		}
		pthread_mutex_lock(&philo->l_fork->mutex);
		if (!philo->l_fork->available)
		{
			pthread_mutex_unlock(&philo->r_fork->mutex);
			pthread_mutex_unlock(&philo->l_fork->mutex);
			return (0);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		if (!philo->l_fork->available)
		{
			pthread_mutex_unlock(&philo->l_fork->mutex);
			return (0);
		}
		pthread_mutex_lock(&philo->r_fork->mutex);
		if (!philo->r_fork->available)
		{
			pthread_mutex_unlock(&philo->l_fork->mutex);
			pthread_mutex_unlock(&philo->r_fork->mutex);
			return (0);
		}
	}
	return (1);
}

int	ft_sem_post(t_philo *philo)
{
	while (!are_forks_available(philo))
	{
		if (is_dead(philo))
			return (1);
	}
	//pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->available = 0;
	pthread_mutex_lock(&philo->data->write);
	printf("%dms philo %d has taken his right fork\n", get_time()
		- philo->data->init_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	//pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->available = 0;
	pthread_mutex_lock(&philo->data->write);
	printf("%dms philo %d has taken his left fork\n", get_time()
		- philo->data->init_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_lock(&philo->state);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	philo->time_to_die = get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->state);
	if (is_dead(philo))
		return 1;
	int dead = start_eating(philo);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->available = 1;
	if (!dead){
		pthread_mutex_lock(&philo->data->write);
		printf("%dms philo %d has dropped his left fork\n", get_time()
			- philo->data->init_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->available = 1;
	if (!dead){
		pthread_mutex_lock(&philo->data->write);
		printf("%dms philo %d has dropped his right fork\n", get_time()
			- philo->data->init_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);}
	pthread_mutex_unlock(&philo->r_fork->mutex);
	if (is_dead(philo))
		return 1;
	start_sleeping(philo);
	if (is_dead(philo))
		return 1;
	return (0);
}

int	ft_sem_destroy(t_semaphore *sem)
{
	pthread_mutex_destroy(&sem->mutex);
	// free(sem);
	return (0);
}