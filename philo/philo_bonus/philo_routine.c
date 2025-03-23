/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:19:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 15:55:26 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosopher_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->shared->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->shared->meal_lock);
	if (philo->id % 2 != 0)
		ft_usleep(philo->shared->time_to_eat / 2);
	while (!is_simulation_over(philo->shared))
	{
		philo_eat(philo);
		if (philo->shared->num_times_to_eat != -1
			&& philo->meals_eaten >= philo->shared->num_times_to_eat)
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->shared->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	handle_one_philo(t_philosophers *philosophers)
{
	printf("%zu %d %s\n", get_time() - philosophers->start_time, 1,
		"has taken a fork");
	ft_usleep(philosophers->time_to_die);
	printf("%zu %d %s\n", get_time() - philosophers->start_time, 1, "die");
}

void	*superviseur(void	*arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers*) arg;
	while (1)
	{
		sem_wait(&philosophers->meal_lock);
		if (get_time() - philosophers->last_meal >= philosophers->time_to_die)
		{
			sem_wait(&philosophers->write_lock);
			printf("%zu %d %s\n", get_time() - philosophers->start_time, 1, "die");
			exit (0);
		}
		sem_post(&philosophers->meal_lock);
		if ()
	}
}