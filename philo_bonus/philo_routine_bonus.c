/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:19:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/14 09:19:59 by noel-baz         ###   ########.fr       */
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

void	handle_one_philo(t_philosophers *philosophers)
{
	printf("%zu %d %s\n", get_time() - philosophers->start_time, 1,
		"has taken a fork");
	ft_usleep(philosophers->time_to_die);
	printf("%zu %d %s\n", get_time() - philosophers->start_time, 1, "die");
	exit(0);
}

void	*superviseur(void	*arg)
{
	t_philosophers	*philosophers;
	size_t			last_meal;
	size_t			current;
	int				meal;

	philosophers = (t_philosophers*) arg;
	while (1)
	{
		current = get_time();
		sem_wait(philosophers->meal_lock);
		last_meal = philosophers->last_meal;
		meal = philosophers->meals_eaten;
		sem_post(philosophers->meal_lock);
		if (current - last_meal > philosophers->time_to_die)
		{
			sem_wait(philosophers->write_lock);
			printf("%zu %d %s\n", get_time() - philosophers->start_time, philosophers->id, "died");
			exit(1);
		}
		if (philosophers->num_times_to_eat != -1
			&& (meal >= philosophers->num_times_to_eat))
			exit(0);
		usleep(100);
	}
	return (NULL);
}
