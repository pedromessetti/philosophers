/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:23:02 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 16:29:42 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_ac(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong amount of arguments\n");
		printf("Arguments:\n\t./philo\n\tnumber_of_philosophers\n\t");
		printf("time_to_die\n\ttime_to_eat\n\ttime_to_sleep\n\t");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

int	check_av(char **av)
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;

	number_of_philos = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		number_of_times_each_philosopher_must_eat = 0;
	if (number_of_philos < 1 || number_of_philos > 200 || time_to_die < 0
		|| time_to_eat < 0 || time_to_sleep < 0
		|| number_of_times_each_philosopher_must_eat < 0)
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	return (1);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (get_time() >= philo->time_to_die)
	{
		if (philo->data->dead == 0)
		{
			philo->data->dead = 1;
			pthread_mutex_lock(&philo->data->write);
			printf("%dms philo %d died\n", get_time() - philo->data->init_time,
				philo->id);
			pthread_mutex_unlock(&philo->data->write);
		}
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	none_meals_case(t_philo *philo)
{
	if (philo->data->number_of_meals == 0 || philo->data->number_of_philos == 1)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%dms philo %d is thinking\n", get_time()
			- philo->data->init_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
		usleep(philo->data->time_to_die * 1000);
		is_dead(philo);
		return (1);
	}
	return (0);
}

int	are_forks_available(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!case_impar(philo))
			return (0);
	}
	else
	{
		if (!case_par(philo))
			return (0);
	}
	return (1);
}
