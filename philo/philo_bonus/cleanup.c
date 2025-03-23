/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:23:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 11:28:17 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_resources(t_philosophers *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->num_of_philos)
	{
		pthread_join(philosophers->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philosophers->num_of_philos)
	{
		pthread_mutex_destroy(&philosophers->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philosophers->dead_lock);
	pthread_mutex_destroy(&philosophers->meal_lock);
	pthread_mutex_destroy(&philosophers->write_lock);
	free(philosophers->forks);
	free(philosophers->philo);
}
