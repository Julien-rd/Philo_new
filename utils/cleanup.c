/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:34:56 by jromann           #+#    #+#             */
/*   Updated: 2025/10/16 17:19:05 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cleanup(t_philosopher *philo, t_data *data, int flag, char *msg)
{
	size_t	iter;

	iter = 0;
	pthread_mutex_destroy(&data->main_mutex);
	while (data->forks && iter < data->philo_amount)
	{
		pthread_mutex_destroy(&data->forks[iter]);
		iter++;
	}
	if (data->forks)
		free(data->forks);
	if (philo)
		free(philo);
	if (msg != NULL)
		safe_write(2, msg, ft_strlen(msg), data);
	if (flag == FAILURE || (data->open_threads != data->philo_amount
			&& data->philo_amount != 1) || data->function_fail == true)
		return (1);
	if (flag == SUCCESS)
		return (0);
	return (0);
}
