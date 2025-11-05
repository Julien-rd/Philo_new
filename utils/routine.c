/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:39:56 by jromann           #+#    #+#             */
/*   Updated: 2025/11/05 13:22:05 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_for_threads(t_philosopher *philo)
{
	while (philo->data->threads_ready == false && simulation_active(philo))
	{
		if (usleep(10) == -1)
			philo->data->function_fail = true;
	}
}

void	*one_philo(void *ptr)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ptr;
	philo->data->start_time = gettime(philo);
	print_num(gettime(philo), philo->data);
	pthread_mutex_lock(&philo->data->forks[0]);
	safe_write(1, " 1 has picked up a fork\n", 24, philo->data);
	optimised_usleep(philo->data->time_to_die, philo);
	print_num(gettime(philo), philo->data);
	pthread_mutex_unlock(&philo->data->forks[0]);
	safe_write(1, " 1 has died\n", 12, philo->data);
	return (NULL);
}

void	routine_for_even(t_philosopher *philo)
{
	while (simulation_active(philo))
	{
		nap(philo);
		if (philo->data->status == INACTIVE
			|| philo->data->function_fail == true)
			break ;
		think(philo);
		if (philo->data->status == INACTIVE
			|| philo->data->function_fail == true)
			break ;
		eat(philo);
	}
}

void	*routine(void *ptr)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ptr;
	wait_for_threads(philo);
	if (philo->data->philo_amount % 2 == 0 && philo->id % 2 == 0)
		routine_for_even(philo);
	while (simulation_active(philo))
	{
		eat(philo);
		if (philo->data->status == INACTIVE
			|| philo->data->function_fail == true)
			break ;
		nap(philo);
		if (philo->data->status == INACTIVE
			|| philo->data->function_fail == true)
			break ;
		think(philo);
	}
	return (NULL);
}
