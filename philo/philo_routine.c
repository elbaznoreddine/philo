/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:19:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/16 13:03:51 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 || philo->id == philo->shared->num_of_philos)
		ft_usleep(philo->shared->time_to_eat / 2, philo->shared);
	while (1)
	{
		if (is_simulation_over(philo->shared))
			break ;
		philo_eat(philo);
		if (is_simulation_over(philo->shared))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->shared->time_to_sleep, philo->shared);
		if (is_simulation_over(philo->shared))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->shared->write_lock);
	printf("%zu %d %s\n", get_time() - philo->shared->start_time, 1,
		"has taken a fork");
	pthread_mutex_unlock(&philo->shared->write_lock);
	ft_usleep(philo->shared->time_to_die, philo->shared);
	pthread_mutex_lock(&philo->shared->write_lock);
	printf("%zu %d %s\n", get_time() - philo->shared->start_time, 1, "died");
	pthread_mutex_unlock(&philo->shared->write_lock);
	pthread_mutex_lock(philo->l_fork);
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
