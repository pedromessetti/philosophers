/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:35:05 by pedro             #+#    #+#             */
/*   Updated: 2023/08/08 07:06:02 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sem_init(t_semaphore *sem)
{
	sem->available = 1;
	pthread_mutex_init(&sem->mutex, NULL);
	return (0);
}

int	ft_sem_wait(t_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
    while (sem->available == 0) {
        pthread_mutex_unlock(&sem->mutex);
		pthread_mutex_lock(&sem->mutex);
    }
	sem->available--;
	pthread_mutex_unlock(&sem->mutex);
	return (0);
}

int	ft_sem_post(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	printf("%dms philo %d has taken his right fork\n", get_time() - philo->data->init_time, philo->id);
	pthread_mutex_lock(&philo->l_fork->mutex);
	printf("%dms philo %d has taken his left fork\n", get_time() - philo->data->init_time, philo->id);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time() + philo->data->time_to_die;
	start_eating(philo);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	printf("%dms philo %d has dropped his left fork\n", get_time() - philo->data->init_time, philo->id);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	printf("%dms philo %d has dropped his right fork\n", get_time() - philo->data->init_time, philo->id);
	start_sleeping(philo);
	return (0);
}

int	ft_sem_destroy(t_semaphore *sem)
{
	pthread_mutex_destroy(&sem->mutex);
	free(sem);
	return (0);
}