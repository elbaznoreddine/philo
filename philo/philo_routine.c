/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:19:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/18 14:40:09 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    philo->last_meal = philo->shared->start_time;
    if (philo->id % 2 != 0)
        ft_usleep(15);
    while (!is_simulation_over(philo->shared))
    {
        philo_eat(philo);
        if (philo->shared->num_times_to_eat != -1 && 
            philo->meals_eaten >= philo->shared->num_times_to_eat)
            break;
        print_status(philo, "is sleeping");
        ft_usleep(philo->shared->time_to_sleep);
        print_status(philo, "is thinking");
    }
    return (NULL);
}