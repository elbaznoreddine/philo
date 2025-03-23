/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:19:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 11:33:03 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

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

int	is_simulation_over(t_philosophers *philosophers)
{
	pthread_mutex_lock(&philosophers->dead_lock);
	if (philosophers->dead_flag)
	{
		pthread_mutex_unlock(&philosophers->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philosophers->dead_lock);
	return (0);
}
