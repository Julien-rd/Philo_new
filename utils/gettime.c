/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:43:41 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 15:46:27 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	gettime(t_philosopher *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		philo->data->function_fail = true;
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->data->start_time);
}
