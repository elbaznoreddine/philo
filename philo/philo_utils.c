/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:40:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 10:49:38 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long	ft_atoi(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] <= '9' && str[i] >= '0'))
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	while (is_space(str[i]))
		i++;
	if (str[i] == '\0')
		return (result);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	size_t	current_time;

	pthread_mutex_lock(&philo->shared->write_lock);
	if (!is_simulation_over(philo->shared))
	{
		current_time = get_time() - philo->shared->start_time;
		printf("%zu %d %s\n", current_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->shared->write_lock);
}
