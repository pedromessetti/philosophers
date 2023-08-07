/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:23:02 by pedro             #+#    #+#             */
/*   Updated: 2023/08/03 20:25:59 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_ac(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong amount of arguments\nArguments:\n\t./philo\n\tnumber_of_philosophers\n\ttime_to_die\n\ttime_to_eat\n\ttime_to_sleep\n\t[number_of_times_each_philosopher_must_eat]\n");
		return(1);
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
		return (-1);
	}
	return (1);
}
