/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:00:10 by pedro             #+#    #+#             */
/*   Updated: 2023/08/03 16:11:45 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int result;
	int i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] && !ft_isnum(str[i]))
		return (-1);
	while (ft_isnum(str[i]))
	{
		result *= 10;
		result += str[i] - 48;
		i++;
		if (str[i] && !ft_isnum(str[i]))
			return (-1);
	}
	return (result);
}
