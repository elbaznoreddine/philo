/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:09:04 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/18 14:56:48 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_simulation_over(t_philosophers *philos)
{
	pthread_mutex_lock(&philos->dead_lock);
	if (philos->dead_flag)
	{
		pthread_mutex_unlock(&philos->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philos->dead_lock);
	return (0);
}

void print_status(t_philo *philo, char *status)
{
    size_t current_time;
    
    pthread_mutex_lock(&philo->shared->write_lock);
    
    if (!is_simulation_over(philo->shared))
    {
        current_time = get_time() - philo->shared->start_time;
        printf("%zu %d %s\n", current_time, philo->id, status);
    }
    pthread_mutex_unlock(&philo->shared->write_lock);
}

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->l_fork);
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
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

int start_simulation(t_philosophers *philos)
{
    int i;

    philos->start_time = get_time();
    i = 0;
    while (i < philos->num_of_philos)
    {
        philos->philos[i].last_meal = philos->start_time;
        if (pthread_create(&philos->philos[i].thread, NULL,
                          philosopher_routine, &philos->philos[i]) != 0)
            return (0);
        i++;
    }
    return (1);
}

void monitor_simulation(t_philosophers *philos)
{
    int i;
    int all_ate_enough;
    size_t current_time;
    
    while (1)
    {
        i = 0;
        all_ate_enough = 1;
        
        while (i < philos->num_of_philos)
        {
            pthread_mutex_lock(&philos->meal_lock);
            current_time = get_time();
            if (!philos->philos[i].eating && 
                (current_time - philos->philos[i].last_meal) >= philos->time_to_die)
            {
                if (!is_simulation_over(philos))
                {
                    print_status(&philos->philos[i], "died");
                    pthread_mutex_lock(&philos->dead_lock);
                    philos->dead_flag = 1;
                    pthread_mutex_unlock(&philos->dead_lock);
                }
                pthread_mutex_unlock(&philos->meal_lock);
                return;
            }
            if (philos->num_times_to_eat != -1 && 
                philos->philos[i].meals_eaten < philos->num_times_to_eat)
                all_ate_enough = 0;
            pthread_mutex_unlock(&philos->meal_lock);
            i++;
        }
        if (philos->num_times_to_eat != -1 && all_ate_enough)
        {
            pthread_mutex_lock(&philos->dead_lock);
            philos->dead_flag = 1;
            pthread_mutex_unlock(&philos->dead_lock);
            break;
        }
        ft_usleep(1);
    }
}
