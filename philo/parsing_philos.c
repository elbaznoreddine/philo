/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:45:35 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/21 07:25:31 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_philos(t_philosophers *philos, char **av)
{
	philos->num_of_philos = (int)ft_atoi(av[1]);
	philos->time_to_die = (int)ft_atoi(av[2]);
	philos->time_to_eat = (int)ft_atoi(av[3]);
	philos->time_to_sleep = (int)ft_atoi(av[4]);
	
	if (av[5])
		philos->num_times_to_eat = ft_atoi(av[5]);
	else
		philos->num_times_to_eat = -1;
	if (philos->num_of_philos <= 0 || philos->time_to_die <= 0
	|| philos->time_to_eat <= 0 || philos->time_to_sleep <= 0
	|| (av[5] && (philos->num_times_to_eat <= 0)))
		return (0);
	return (1);
}

int	init_philosophers(t_philosophers *philos)
{
	int	i;

	if (pthread_mutex_init(&philos->dead_lock, NULL) != 0
		|| pthread_mutex_init(&philos->meal_lock, NULL) != 0
		|| pthread_mutex_init(&philos->write_lock, NULL) != 0)
			return (0);
	philos->forks = malloc(sizeof(pthread_mutex_t) * philos->num_of_philos);
	if (!philos->forks)
		return (0);
	i = 0;
	while (i < philos->num_of_philos)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (!init_threads(philos))
		return (0);
	return (1);
}
int	init_threads(t_philosophers *philos)
{
	int	i;

	i = 0;
	philos->philos = malloc(sizeof(t_philo) * philos->num_of_philos);
	if (!philos->philos)  
		return (0);
	philos->dead_flag = 0;
	while (i < philos->num_of_philos)
	{
		philos->philos[i].id = i + 1;
		philos->philos[i].eating = 0;
		philos->philos[i].meals_eaten = 0;
		philos->philos[i].last_meal = 0;
		philos->philos[i].shared = philos;
		if (i == philos->num_of_philos - 1)
		{
			philos->philos[i].r_fork = &philos->forks[0];
			philos->philos[i].l_fork = &philos->forks[i];
		}
		else
		{
			philos->philos[i].r_fork = &philos->forks[i];
			philos->philos[i].l_fork = &philos->forks[i + 1];
		}
		i++;
	}
	return (1);
}
