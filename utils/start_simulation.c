/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/10/16 17:13:23 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	initialise_philos(t_data *data, t_philosopher **philo)
{
	size_t	iter;

	iter = 0;
	*philo = malloc(sizeof(t_philosopher) * data->philo_amount);
	if (!*philo)
		return ;
	while (iter < data->philo_amount)
	{
		(*philo)[iter].id = iter + 1;
		(*philo)[iter].left_fork = 0;
		(*philo)[iter].right_fork = 0;
		(*philo)[iter].data = data;
		(*philo)[iter].time_alive = 0;
		(*philo)[iter].eaten_meals = 0;
		(*philo)[iter].last_eaten = 0;
		(*philo)[iter].ready = NOTREADY;
		if (data->philo_amount == 1 && protected_pthread_create(*philo, iter,
				one_philo) == 1)
			break ;
		else if (data->philo_amount > 1 && protected_pthread_create(*philo,
				iter, routine) == 1)
			break ;
		iter++;
		data->open_threads = iter;
	}
}

static int	monitoring_philos(t_data *data, t_philosopher **philo)
{
	if (data->status == ACTIVE)
	{
		if (data->philo_amount == 1)
			return (0);
		dinner_done(*philo);
		if (data->open_threads != data->philo_amount)
			data->status = INACTIVE;
		pthread_mutex_lock(&data->main_mutex);
		data->start_time = gettime(*philo);
		data->threads_ready = true;
		pthread_mutex_unlock(&data->main_mutex);
		while (data->philo_amount != 1 && data->status == ACTIVE
			&& data->function_fail == false)
		{
			if (status_check(*philo) == 1)
				return (data->status = INACTIVE, 1);
			if (usleep(0) == -1)
				return (data->function_fail = true, data->status = INACTIVE, 1);
		}
	}
	return (0);
}

static void	join_philos(t_data *data, t_philosopher **philo)
{
	size_t	iter;

	iter = 0;
	while (iter < data->open_threads)
	{
		pthread_join((*philo)[iter].newthread, NULL);
		iter++;
	}
}

int	start_simulation(t_data *data)
{
	t_philosopher	*philo;

	initialise_philos(data, &philo);
	if (philo == NULL)
		return (cleanup(philo, data, FAILURE, NULL));
	monitoring_philos(data, &philo);
	join_philos(data, &philo);
	return (cleanup(philo, data, SUCCESS, NULL));
}
