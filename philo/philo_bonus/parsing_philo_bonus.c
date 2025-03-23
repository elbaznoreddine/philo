/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:32:42 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 15:41:31 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_philos(t_philosophers *philosophers, char **av)
{
	philosophers->num_of_philos = (int)ft_atoi(av[1]);
	philosophers->time_to_die = (int)ft_atoi(av[2]);
	philosophers->time_to_eat = (int)ft_atoi(av[3]);
	philosophers->time_to_sleep = (int)ft_atoi(av[4]);
	if (av[5])
		philosophers->num_times_to_eat = ft_atoi(av[5]);
	else
		philosophers->num_times_to_eat = -1;
	if (philosophers->num_of_philos <= 0 || philosophers->time_to_die <= 0
		|| philosophers->time_to_eat <= 0 || philosophers->time_to_sleep <= 0
		|| (av[5] && (philosophers->num_times_to_eat <= 0)))
		return (0);
	philosophers->philos = malloc(philosophers->num_of_philos);
	if (!philosophers->philos)
		return (0);
	philosophers->forks = NULL;
	philosophers->write_lock = NULL;
	philosophers->meal_lock = NULL;
	philosophers->start_time = 0;
	philosophers->meals_eaten = 0;
	philosophers->last_meal = 0;
	if(!init_semaphore(philosophers))
		return (0);
	return (1);
}
static int	init_semaphore(t_philosophers *philosophers)
{
	sem_unlink("/meal_lock");
	sem_unlink("/write_lock");
	sem_unlink("/forks");
	philosophers->meal_lock = sem_open("/meal_lock", O_CREAT, 0644, 1);
	philosophers->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	philosophers->forks = sem_open("/forks", O_CREAT, 0644, philosophers->num_of_philos);
	if (philosophers->meal_lock == SEM_FAILED
		|| philosophers->write_lock == SEM_FAILED
		|| philosophers->forks == SEM_FAILED)
		return (0);
	return (1);
}

int	init_philosophers(t_philosophers	*philosophers)
{
	int		i;

	i = -1;
	while (++i < philosophers->num_of_philos)
	{
		philosophers->philos[i] = fork();
		if (philosophers->philos[i] == -1)
			return (0);
		if (philosophers->philos[i] == 0)
		{
			philosophers->id = i + 1;
			philosophers->last_meal = philosophers->start_time;
			if (pthread_create(&philosophers->thread_monitor, NULL,superviseur, &philosophers))
				return (0);
			if (pthread_detach(philosophers->thread_monitor) != 0)
				return (0);
			philosopher_routine(philosophers);
		}
	}
}