/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:34:16 by jromann           #+#    #+#             */
/*   Updated: 2025/10/16 16:34:04 by jromann          ###   ########.fr       */
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
