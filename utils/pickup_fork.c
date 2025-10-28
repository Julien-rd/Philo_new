/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:34:08 by jromann           #+#    #+#             */
/*   Updated: 2025/10/16 17:19:01 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pickup_fork(t_philosopher *philo)
{
	size_t	left;
	size_t	right;

	left = philo->id - 1;
	right = philo->id % philo->data->philo_amount;
	if (left < right)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		printaction(" has taken a fork\n", philo);
		pthread_mutex_lock(&philo->data->forks[right]);
		printaction(" has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		printaction(" has taken a fork\n", philo);
		pthread_mutex_lock(&philo->data->forks[left]);
		printaction(" has taken a fork\n", philo);
	}
	philo->left_fork = 1;
	philo->right_fork = 1;
}
