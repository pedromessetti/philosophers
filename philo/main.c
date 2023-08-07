/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:24 by pedro             #+#    #+#             */
/*   Updated: 2023/08/03 23:11:44 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	printf("philo %d is eating\n", philo->id);
}

void *routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		eat(philo);
		printf("philo %d is thinking\n", philo->id);
	}
	if (pthread_join(philo->thread, NULL))
		return ((void *)1);
	return ((void *)0);
}

void	init_threads(t_data *data)
{
	int				i;
	struct timeval	tv;

	i = -1;
	data->starting_time = gettimeofday(&tv, NULL);
	while (++i < data->number_of_philos)
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(data->philos[i].thread, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_ac(ac))
		return (1);
	if (check_av(av) == -1)
		return (1);
	if (init(av, &data))
		return (1);
	init_threads(&data);
	return (0);
}
