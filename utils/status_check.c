/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/11/05 13:30:40 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	simulation_active(t_philosopher *philo)
{
	if (philo->data->status == INACTIVE || philo->data->function_fail == true)
		return (0);
	return (1);
}

static void	alive_check(t_philosopher *philo)
{
	size_t	iter;
	size_t	time;

	iter = 0;
	while (iter < philo->data->philo_amount)
	{
		time = gettime(philo);
		if (time - philo[iter].last_eaten > philo->data->time_to_die)
		{
			print_num(gettime(&philo[iter]), philo->data);
			safe_write(1, " ", 1, philo->data);
			print_num(philo[iter].id, philo->data);
			safe_write(1, " died\n", 6, philo->data);
			philo->data->status = 0;
			return ;
		}
		iter++;
	}
}

int	dinner_done(t_philosopher *philo)
{
	if (philo->data->philos_done == philo->data->philo_amount)
	{
		safe_write(1, "dinner done!\n", 13, philo->data);
		philo->data->status = 0;
		return (1);
	}
	return (0);
}

int	function_failed(t_philosopher *philo)
{
	if (philo->data->function_fail)
		philo->data->status = 0;
	return (philo->data->function_fail);
}

int	status_check(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->main_mutex);
	if (!function_failed(philo) && !dinner_done(philo))
		alive_check(philo);
	pthread_mutex_unlock(&philo->data->main_mutex);
	return (0);
}
