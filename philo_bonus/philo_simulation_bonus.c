/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:09:04 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/14 10:58:32 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_take(t_philosophers *philosophers)
{
	sem_wait(philosophers->forks);
	print_status(philosophers, "has taken a fork");
	sem_wait(philosophers->forks);
	print_status(philosophers, "has taken a fork");
}

void	philo_eat(t_philosophers *philosophers)
{
	
	print_status(philosophers, "is eating");
	ft_usleep(philosophers->time_to_eat);
	sem_wait(philosophers->meal_lock);
	philosophers->last_meal = get_time();
	philosophers->meals_eaten++;
	sem_post(philosophers->meal_lock);
}

void	philo_sleep(t_philosophers *philosophers)
{
	sem_post(philosophers->forks);
	sem_post(philosophers->forks);
	print_status(philosophers, "is sleeping");
	ft_usleep(philosophers->time_to_sleep);
	print_status(philosophers, "is thinking");
}
