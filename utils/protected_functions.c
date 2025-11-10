/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:34:16 by jromann           #+#    #+#             */
/*   Updated: 2025/11/06 17:24:19 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	protected_pthread_create(t_philosopher *philo, int pos, void *function)
{
	if (pthread_create(&philo[pos].newthread, NULL, function,
			(int *)&philo[pos]) != 0)
		return (1);
	return (0);
}

int	safe_write(int fd, char *str, int size, t_data *data)
{
	if (data->function_fail == true)
		return (-1);
	if (write(fd, str, size) == -1)
	{
		data->function_fail = true;
		return (-1);
	}
	return (0);
}
