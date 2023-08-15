/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:24 by pedro             #+#    #+#             */
/*   Updated: 2023/08/15 16:32:32 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		if (data->finished >= data->number_of_philos)
		{
			data->dead = 1;
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(1000);
	}
	return ((void *)0);
}

void	*routine(void *thread_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)thread_pointer;
	philo->time_to_die = philo->data->time_to_die + get_time();
	if (none_meals_case(philo))
		return ((void *)0);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (ft_sem_post(philo))
			break ;
		if (philo->meals_count == philo->data->number_of_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		if (is_dead(philo))
			break ;
		message(philo);
	}
	return ((void *)0);
}

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

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	data->init_time = get_time();
	if (data->number_of_meals >= 0)
		pthread_create(&monitor_thread, NULL, (void *(*)(void *))monitor, data);
	while (++i < data->number_of_philos)
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(data->philos[i].thread, NULL);
	if (data->number_of_meals >= 0)
		pthread_join(monitor_thread, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_ac(ac))
		return (1);
	if (!check_av(av))
		return (1);
	if (init(av, &data))
		return (1);
	start_simulation(&data);
	end_simulation(&data);
	return (0);
}
