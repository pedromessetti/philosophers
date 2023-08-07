/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:35:05 by pedro             #+#    #+#             */
/*   Updated: 2023/08/03 14:44:20 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* The function initializes a semaphore with a given count.
* 
* @param sem The parameter "sem" is a pointer to a structure of type "t_semaphore".
* @param count The count parameter is an integer that represents the initial value of the semaphore.
* It determines the number of resources available for concurrent access.
* 
* @return 0.
*/
int	ft_sem_init(t_semaphore *sem, int count)
{
	sem->count = count;
	pthread_mutex_init(&sem->mutex, NULL);
	return (0);
}

/**
* The function waits until the semaphore count is greater than 0, decrements the count,
* and returns 0.
* 
* @param sem The parameter "sem" is a pointer to a structure of type "t_semaphore".
* 
* @return 0.
*/
int	ft_sem_wait(t_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
    while (sem->count == 0) {
        pthread_mutex_unlock(&sem->mutex);
        pthread_mutex_lock(&sem->mutex);
    }
	sem->count--;
	pthread_mutex_unlock(&sem->mutex);
	return (0);
}

/**
* The function increases the count of a semaphore and signals a waiting thread.
* 
* @param sem The parameter "sem" is a pointer to a structure of type "t_semaphore".
* 
* @return 0.
*/
int	ft_sem_post(t_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
	sem->count++;
	pthread_mutex_unlock(&sem->mutex);
	return (0);
}

/**
* The function  destroys a semaphore by destroying its mutex and condition variable
* and freeing the memory allocated for the semaphore structure.
* 
* @param sem The parameter "sem" is a pointer to a structure of type "t_semaphore".
* 
* @return 0.
*/
int	ft_sem_destroy(t_semaphore *sem)
{
	pthread_mutex_destroy(&sem->mutex);
	free(sem);
	return (0);
}