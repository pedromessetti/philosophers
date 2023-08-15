/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:00:10 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 09:10:09 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		ft_sem_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].state);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	free(data->thread_id);
	free(data->forks);
	free(data->philos);
}

int	get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int     ft_atoi(char *str)
{
	int     i;
	int     sign;
	int     result;

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
	while (ft_isnum(str[i]))
	{
			result *= 10;
			result += str[i] - 48;
			i++;
	}
	return (result * sign);
}
