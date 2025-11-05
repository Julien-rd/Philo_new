/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:52:18 by jromann           #+#    #+#             */
/*   Updated: 2025/11/05 13:06:42 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialise_data(t_data *data, int argc, char **argv)
{
	if (valid_input(argc, argv) == 1)
		return (1);
	if (initialise_args(data, argc, argv) == 1)
		return (1);
	if (pthread_mutex_init(&data->main_mutex, NULL) != 0)
		return (write(2, "PTHREAD_MUTEX_INIT FAILED\n", 26), 1);
	if (initialise_forks(data) == 1)
		return (1);
	return (0);
}
