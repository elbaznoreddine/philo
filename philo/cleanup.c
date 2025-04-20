/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:23:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/20 06:01:40 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cleanup_resources(t_philosophers *philosophers)
{
	int	i;

	i = 0;
	if (philosophers->num_of_philos == 1)
	{
		if (pthread_join(philosophers->philo[i].thread, NULL) != 0)
			return (0);
	}
	else
	{
		while (i < philosophers->num_of_philos)
		{
			if (pthread_join(philosophers->philo[i].thread, NULL))
				return (0);
			i++;
		}
	}
	cleanup_error(philosophers);
	return (1);
}

void	cleanup_error(t_philosophers *philosophers)
{
	int	i;

	i = 0;
	if (philosophers->forks)
	{
		while (i < philosophers->num_of_philos)
		{
			pthread_mutex_destroy(&philosophers->forks[i]);
			i++;
		}
		free(philosophers->forks);
	}
	pthread_mutex_destroy(&philosophers->dead_lock);
	pthread_mutex_destroy(&philosophers->meal_lock);
	pthread_mutex_destroy(&philosophers->write_lock);
	if (philosophers->philo)
		free(philosophers->philo);
}
