/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:45:37 by pedro             #+#    #+#             */
/*   Updated: 2023/08/08 06:59:42 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks_and_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].meals_count = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		data->philos[i].l_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].r_fork = &data->forks[data->number_of_philos - 1];
		else
			data->philos[i].r_fork = &data->forks[i - 1];
		ft_sem_init(&data->forks[i]);
	}
}

int	init(char **av, t_data *data)
{
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = -1;
	data->dead = 0;
	data->finished = 0;
	data->thread_id = malloc(sizeof(pthread_t) * data->number_of_philos);
	data->forks = malloc(sizeof(t_semaphore) * data->number_of_philos);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos || !data->forks || !data->thread_id)
		return (1);
	set_forks_and_philos(data);
	return (0);
}
