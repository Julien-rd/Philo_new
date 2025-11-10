/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/11/10 14:07:51 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ready2eat(t_philosopher *philo, size_t iter, size_t iter_max)
{
	if (iter == 0)
	{
		if (philo[iter].eaten_meals <= philo[iter + 1].eaten_meals
			&& philo[iter].eaten_meals <= philo[iter_max].eaten_meals)
			philo[iter].ready = true;
		else
			philo[iter].ready = false;
	}
	else if (iter == iter_max)
	{
		if (philo[iter].eaten_meals <= philo[0].eaten_meals
			&& philo[iter].eaten_meals <= philo[iter - 1].eaten_meals)
			philo[iter].ready = true;
		else
			philo[iter].ready = false;
	}
	else
	{
		if (philo[iter].eaten_meals <= philo[iter + 1].eaten_meals
			&& philo[iter].eaten_meals <= philo[iter - 1].eaten_meals)
			philo[iter].ready = true;
		else
			philo[iter].ready = false;
	}
}

static void	alive_check(t_philosopher *philo)
{
	size_t	iter;
	size_t	time;

	iter = 0;
	while (iter < philo->data->philo_amount)
	{
		time = gettime(philo);
		ready2eat(philo, iter, philo->data->philo_amount - 1);
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
		philo->data->status = 0;
		safe_write(1, "dinner done!\n", 13, philo->data);
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
