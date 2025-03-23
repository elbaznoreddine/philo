/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:32:42 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 12:40:31 by noel-baz         ###   ########.fr       */
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
	return (1);
}
int	init_philosophers(t_philosophers philosophers)
{
	
}