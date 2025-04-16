/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:45:35 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/15 19:26:00 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_philos(t_philosophers *philosophers, char **av)
{
	philosophers->num_of_philos = (int)ft_atoi(av[1]);
	philosophers->time_to_die = (size_t)ft_atoi(av[2]);
	philosophers->time_to_eat = (size_t)ft_atoi(av[3]);
	philosophers->time_to_sleep = (size_t)ft_atoi(av[4]);
	if (av[5])
		philosophers->num_times_to_eat = (int)ft_atoi(av[5]);
	else
		philosophers->num_times_to_eat = -1;
	if (philosophers->num_of_philos <= 0 || philosophers->time_to_die <= 0
		|| philosophers->time_to_eat <= 0 || philosophers->time_to_sleep <= 0
		|| (av[5] && (philosophers->num_times_to_eat <= 0)))
		return (0);
	philosophers->start_time = get_time();
	philosophers->dead_flag = 0;
	return (1);
}

static int	create_forks(t_philosophers	*philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->num_of_philos)
	{
		if (pthread_mutex_init(&philosophers->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&philosophers->forks[--i]);
			return (free(philosophers->forks), 0);
		}
		i++;
	}
	return (1);
}

int	init_philosophers(t_philosophers *philosophers)
{
	if (pthread_mutex_init(&philosophers->dead_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philosophers->meal_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philosophers->write_lock, NULL) != 0)
		return (0);
	philosophers->forks = malloc(sizeof(pthread_mutex_t)
			* philosophers->num_of_philos);
	if (!philosophers->forks)
		return (0);
	if (!create_forks(philosophers))
		return (0);
	philosophers->philo = malloc(sizeof(t_philo) * philosophers->num_of_philos);
	if (!philosophers->philo)
		return (cleanup_error(philosophers), 0);
	if (!init_threads(philosophers))
		return (cleanup_error(philosophers), 0);
	return (1);
}

int	init_threads(t_philosophers *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->num_of_philos)
	{
		philosophers->philo[i].id = i + 1;
		philosophers->philo[i].meals_eaten = 0;
		philosophers->philo[i].last_meal = philosophers->start_time;
		philosophers->philo[i].shared = philosophers;
		philosophers->philo[i].r_fork = &philosophers->forks[(i + 1)
			% philosophers->num_of_philos];
		philosophers->philo[i].l_fork = &philosophers->forks[i];
		i++;
	}
	return (1);
}
