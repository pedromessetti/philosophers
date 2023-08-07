/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:29 by pedro             #+#    #+#             */
/*   Updated: 2023/08/03 22:40:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* --- MACRO Variables --- */

/* --- Main Structure --- */

struct s_data;

typedef struct s_semaphore
{
	int				count;
	pthread_mutex_t	mutex;
}					t_semaphore;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				count_eat;
	int				status;
	int				eating;
	int				time_to_die;
	pthread_mutex_t	lock;
	t_semaphore		*r_fork;
	t_semaphore		*l_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	pthread_t		*thread_id;
	int				starting_time;
	int				dead;
	int				finished;
	t_philo			*philos;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	t_semaphore		*forks;
}					t_data;

/* --- Checker Functions --- */

int					check_ac(int ac);
int					check_av(char **av);

/* --- Utils Functions --- */

int					ft_isnum(char c);
int					ft_atoi(char *str);

/* --- Semaphore Functions --- */

int					ft_sem_init(t_semaphore *sem, int count);
int					ft_sem_wait(t_semaphore *sem);
int					ft_sem_post(t_semaphore *sem);
int					ft_sem_destroy(t_semaphore *sem);

/* --- Init Functions --- */

void				set_forks_and_philos(t_data *data);
int					init(char **av, t_data *data);

#endif