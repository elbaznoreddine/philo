/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:09:04 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 11:39:28 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->shared->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->shared->meal_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->shared->time_to_eat);
	pthread_mutex_lock(&philo->shared->meal_lock);
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->shared->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	start_simulation(t_philosophers *philosophers)
{
	int	i;

	philosophers->start_time = get_time();
	i = 0;
	if (philosophers->num_of_philos == 1)
		return (handle_one_philo(philosophers), 1);
	while (i < philosophers->num_of_philos)
	{
		philosophers->philo[i].last_meal = philosophers->start_time;
		if (pthread_create(&philosophers->philo[i].thread, NULL,
				philosopher_routine, &philosophers->philo[i]) != 0)
			return (0);
		i++;
	}
	monitor_simulation(philosophers);
	return (1);
}

int	check_philosopher_died(t_philosophers *philosophers, int i,
	size_t current_time)
{
	if (!philosophers->philo[i].eating
		&& (current_time - philosophers->philo[i].last_meal)
		>= philosophers->time_to_die)
	{
		pthread_mutex_lock(&philosophers->dead_lock);
		if (!philosophers->dead_flag)
		{
			philosophers->dead_flag = 1;
			pthread_mutex_unlock(&philosophers->dead_lock);
			printf("%zu %d %s\n", current_time - philosophers->start_time,
				philosophers->philo[i].id, "died");
			return (1);
		}
		pthread_mutex_unlock(&philosophers->dead_lock);
	}
	return (0);
}

int	check_all_ate_enough(t_philosophers *philosopher)
{
	int	i;
	int	all_ate_enough;

	i = 0;
	all_ate_enough = 1;
	if (philosopher->num_times_to_eat == -1)
		return (0);
	while (i < philosopher->num_of_philos)
	{
		pthread_mutex_lock(&philosopher->meal_lock);
		if (philosopher->philo[i++].meals_eaten < philosopher->num_times_to_eat)
		{
			all_ate_enough = 0;
			pthread_mutex_unlock(&philosopher->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&philosopher->meal_lock);
	}
	if (all_ate_enough)
	{
		pthread_mutex_lock(&philosopher->dead_lock);
		philosopher->dead_flag = 1;
		pthread_mutex_unlock(&philosopher->dead_lock);
	}
	return (all_ate_enough);
}

void	monitor_simulation(t_philosophers *philosophers)
{
	int		i;
	size_t	current_time;

	while (1)
	{
		i = 0;
		while (i < philosophers->num_of_philos)
		{
			pthread_mutex_lock(&philosophers->meal_lock);
			current_time = get_time();
			if (check_philosopher_died(philosophers, i, current_time))
			{
				pthread_mutex_unlock(&philosophers->meal_lock);
				return ;
			}
			pthread_mutex_unlock(&philosophers->meal_lock);
			i++;
		}
		if (check_all_ate_enough(philosophers))
			break ;
		usleep(1000);
	}
}
