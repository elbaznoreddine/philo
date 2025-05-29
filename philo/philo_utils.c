/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:40:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/05/12 09:57:03 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] <= '9' && str[i] >= '0'))
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (result);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds, t_philosophers *philosophers)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&philosophers->dead_lock);
		if (philosophers->dead_flag)
		{
			pthread_mutex_unlock(&philosophers->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&philosophers->dead_lock);
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->shared->write_lock);
	if (!is_simulation_over(philo->shared))
	{
		printf("%zu %d %s\n", get_time() - philo->shared->start_time,
			philo->id, status);
	}
	pthread_mutex_unlock(&philo->shared->write_lock);
}

int	create_thread(t_philosophers *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->num_of_philos)
	{
		if (pthread_create(&philosophers->philo[i].thread, NULL,
				philosopher_routine, &philosophers->philo[i]) != 0)
		{
			pthread_mutex_lock(&philosophers->dead_lock);
			philosophers->dead_flag = 1;
			pthread_mutex_unlock(&philosophers->dead_lock);
			while (i > 0)
			{
				if (pthread_detach(philosophers->philo[--i].thread) != 0)
					return (0);
			}
			return (0);
		}
		i++;
	}
	return (1);
}
