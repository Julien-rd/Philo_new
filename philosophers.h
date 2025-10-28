/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:16 by jromann           #+#    #+#             */
/*   Updated: 2025/10/16 17:09:00 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ACTIVE 1
# define INACTIVE 0
# define SUCCESS 1
# define FAILURE 0
# define RIGHT_FORK 0
# define LEFT_FORK 1
# define DEAD 0
# define ALIVE 1
# define NOTREADY 0
# define READY 1

typedef struct s_data
{
	atomic_size_t	philo_amount;
	atomic_size_t	time_to_die;
	atomic_size_t	time_to_eat;
	atomic_size_t	time_to_sleep;
	atomic_size_t	required_meals;
	atomic_size_t	philos_done;
	atomic_size_t	start_time;
	atomic_size_t	open_threads;
	atomic_bool		status;
	atomic_bool		threads_ready;
	atomic_bool		function_fail;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philosopher
{
	atomic_size_t	id;
	atomic_bool		right_fork;
	atomic_bool		left_fork;
	atomic_bool		ready;
	atomic_size_t	time_alive;
	atomic_size_t	last_eaten;
	atomic_size_t	eaten_meals;
	t_data			*data;
	pthread_t		newthread;
}					t_philosopher;

// main
int					initialise_data(t_data *data, int argc, char **argv);
int					start_simulation(t_data *data);

// simulation_helpers
int					cleanup(t_philosopher *philo, t_data *data, int flag,
						char *msg);
size_t				gettime(t_philosopher *philo);
void				*routine(void *ptr);
void				*one_philo(void *ptr);
void				optimised_usleep(size_t time, t_philosopher *philo);
void				pickup_fork(t_philosopher *philo);
int					ready2eat(t_philosopher *philo);
int					status_check(t_philosopher *philo);
int					dinner_done(t_philosopher *philo);

// actions
void				nap(t_philosopher *philo);
void				eat(t_philosopher *philo);
void				think(t_philosopher *philo);
void				printaction(char *str, t_philosopher *philo);

// protected functions
int					protected_pthread_create(t_philosopher *philo, int pos,
						void *function);

// helper
void				print_num(int n, t_data *data);
size_t				ft_strlen(char *str);
int					ft_atoi(const char *nptr, bool *overflow);
int					safe_write(int fd, char *str, int size, t_data *data);

#endif
