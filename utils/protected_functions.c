/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:34:16 by jromann           #+#    #+#             */
/*   Updated: 2025/11/05 13:03:33 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	protected_pthread_create(t_philosopher *philo, int pos, void *function)
{
	if (pthread_create(&philo[pos].newthread, NULL, function,
			(int *)&philo[pos]) < 0)
		return (1);
	return (0);
}

void	safe_usleep(size_t time, t_philosopher *philo)
{
	if (philo->data->function_fail == true || philo->data->status == 0)
		return ;
	if (usleep(time) == -1)
		philo->data->function_fail = true;
	return ;
}

int	safe_write(int fd, char *str, int size, t_data *data)
{
	if (data->function_fail == true || data->status == 0)
		return (-1);
	if (write(fd, str, size) == -1)
	{
		data->function_fail = true;
		return (-1);
	}
	return (0);
}
