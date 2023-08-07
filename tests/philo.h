/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:29 by pedro             #+#    #+#             */
/*   Updated: 2023/08/03 19:50:32 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* --- MACRO Variables --- */

/* --- Main Structure --- */

typedef struct s_philo
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_philo;

/* --- Semaphores Structure --- */

typedef struct s_semaphore
{
	int				count;
	pthread_mutex_t	mutex;
}					t_semaphore;

/* --- Checker Functions --- */

void				check_ac(int ac);
int					check_av(char **av);

/* --- Utils Functions --- */

int					ft_isnum(char c);
int					ft_atoi(char *str);

/* --- Semaphore Functions --- */

int					ft_sem_init(t_semaphore *sem, int count);
int					ft_sem_wait(t_semaphore *sem);
int					ft_sem_post(t_semaphore *sem);
int					ft_sem_destroy(t_semaphore *sem);

#endif