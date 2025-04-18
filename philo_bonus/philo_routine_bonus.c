/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:19:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/24 13:39:30 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosopher_routine(t_philosophers *philosophers)
{
	while (1)
	{
		philo_take(philosophers);
		philo_eat(philosophers);
		philo_sleep(philosophers);
	}
}

void	*superviseur(t_philosophers *philosophers)
{
	size_t			last_meal;
	size_t			current;
	int				meal;

	while (1)
	{
		sem_wait(philosophers->meal_lock);
		last_meal = philosophers->last_meal;
		meal = philosophers->meals_eaten;
		sem_post(philosophers->meal_lock);
		current = get_time();
		if (current - last_meal > philosophers->time_to_die)
		{
			sem_wait(philosophers->write_lock);
			printf("%zu %d %s\n", get_time() - philosophers->start_time,
				philosophers->id, "died");
			exit(1);
		}
		if (philosophers->num_times_to_eat != -1
			&& (meal >= philosophers->num_times_to_eat))
			exit(0);
	}
	return (NULL);
}
