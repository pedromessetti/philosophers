/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:49:29 by pedro             #+#    #+#             */
/*   Updated: 2023/08/16 18:30:50 by pedro            ###   ########.fr       */
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

/* --- Semaphore Structure --- */

struct s_data;

typedef struct s_semaphore
{
	int				available;
	pthread_mutex_t	mutex;
}					t_semaphore;

/* --- Philosopher Structure --- */

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_count;
	int				time_to_die;
	pthread_mutex_t	state;
	t_semaphore		*r_fork;
	t_semaphore		*l_fork;
	struct s_data	*data;
}					t_philo;

/* --- General Structure --- */

typedef struct s_data
{
	pthread_t		*thread_id;
	int				init_time;
	int				dead;
	int				finished;
	t_philo			*philos;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	t_semaphore		*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data;

/* --- Checker Functions --- */

int					check_ac(int ac);
int					check_av(char **av);
int					is_dead(t_philo *philo);
int					special_case(t_philo *philo);
int					are_forks_available(t_philo *philo);

/* --- Utils Functions --- */

int					ft_atoi(char *str);
int					get_time(void);

/* --- Init Functions --- */

int					initialize(char **av, t_data *data);
void				set_forks_and_philos(t_data *data);

/* --- Actions Functions --- */

int					start_eating(t_philo *philo);
int					start_sleeping(t_philo *philo);
void				grab_forks(t_philo *philo);
int					exec_routine(t_philo *philo);

/* --- Simulation Functions --- */

void				start_simulation(t_data *data);
void				end_simulation(t_data *data);
void				*routine(void *thread_pointer);

#endif