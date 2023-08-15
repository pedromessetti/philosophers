/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:00:10 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 16:33:19 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%dms philo %d is thinking\n", get_time() - philo->data->init_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

int	case_impar(t_philo *philo)
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
	return (1);
}

int	case_par(t_philo *philo)
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
	return (1);
}
