/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:24 by pedro             #+#    #+#             */
/*   Updated: 2023/08/16 10:22:24 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *thread_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)thread_pointer;
	philo->time_to_die = philo->data->time_to_die + get_time();
	if (special_case(philo))
		return ((void *)0);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (exec_routine(philo))
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
		pthread_mutex_lock(&philo->data->write);
		printf("%dms philo %d is thinking\n", get_time() - philo->data->init_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	return ((void *)0);
}

void	end_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
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

	i = -1;
	data->init_time = get_time();
	while (++i < data->number_of_philos)
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(data->philos[i].thread, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_ac(ac))
		return (1);
	if (!check_av(av))
		return (1);
	if (initialize(av, &data))
		return (1);
	start_simulation(&data);
	end_simulation(&data);
	return (0);
}
