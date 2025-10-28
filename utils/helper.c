/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:27:48 by jromann           #+#    #+#             */
/*   Updated: 2025/10/16 16:47:11 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_num(int n, t_data *data)
{
	char		buf[12];
	int			i;
	long long	k;

	i = 11;
	buf[i--] = '\0';
	if (n == 0)
	{
		buf[i] = '0';
		if (safe_write(1, &buf[i], 1, data) == -1)
			return ;
	}
	k = (-1 * (n < 0) + 1 * (n > 0)) * (long)n;
	while (k > 0)
	{
		buf[i--] = '0' + (k % 10);
		k /= 10;
	}
	if (n < 0)
		buf[i--] = '-';
	if (safe_write(1, &buf[i + 1], 11 - i - 1, data) == -1)
		return ;
}

size_t	ft_strlen(char *str)
{
	size_t	iter;

	iter = 0;
	while (str[iter])
		iter++;
	return (iter);
}

int	ft_atoi(const char *nptr, bool *overflow)
{
	int			i;
	long int	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i++] - '0');
	if (result > 2147483647 || (result > 2147483648 && sign == '-'))
		return (*overflow = true, 0);
	return (result * sign);
}

void	optimised_usleep(size_t time, t_philosopher *philo)
{
	size_t	end;
	int		remaining;

	if (time == 0 || philo->data->function_fail == true)
		return ;
	remaining = 1;
	end = gettime(philo) + time;
	while (remaining > 0)
	{
		remaining = end - gettime(philo);
		if (remaining > 1000 && usleep((remaining * 1000) / 2) == -1)
		{
			philo->data->function_fail = true;
			return ;
		}
	}
}

int	ready2eat(t_philosopher *philo)
{
	if (philo->right_fork == 1 && philo->left_fork == 1)
		return (1);
	return (0);
}
