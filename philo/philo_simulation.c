/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:09:04 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/22 09:23:22 by noel-baz         ###   ########.fr       */
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
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
    }
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

int start_simulation(t_philosophers *philos)
{
    int i;

    philos->start_time = get_time();
    i = 0;
    if (philos->num_of_philos == 1)
        return (handle_one_philo(philos), 1);
    while (i < philos->num_of_philos)
    {
        philos->philos[i].last_meal = philos->start_time;
        if (pthread_create(&philos->philos[i].thread, NULL,
                          philosopher_routine, &philos->philos[i]) != 0)
            return (0);
        i++;
    }
    monitor_simulation(philos);
    return (1);
}

// void monitor_simulation(t_philosophers *philos)
// {
//     int i;
//     int all_ate_enough;
//     size_t current_time;
    
//     while (1)
//     {
//         i = 0;
//         all_ate_enough = 1;
//         while (i < philos->num_of_philos)
//         {
//             pthread_mutex_lock(&philos->meal_lock);
//             current_time = get_time();
//             if (!philos->philos[i].eating && 
//                 (current_time - philos->philos[i].last_meal) >= philos->time_to_die)
//             {
//                 pthread_mutex_lock(&philos->dead_lock);
//                 if (!philos->dead_flag)
//                 {
//                     philos->dead_flag = 1;
//                     pthread_mutex_unlock(&philos->dead_lock);
//                     printf("%zu %d %s\n", current_time - philos->start_time,
//                         philos->philos[i].id, "die");
//                     pthread_mutex_unlock(&philos->meal_lock);
//                     return ;
//                 }
//                 pthread_mutex_unlock(&philos->dead_lock);
//             }
//             pthread_mutex_unlock(&philos->meal_lock);
//             i++;
//         }
//         if (philos->num_times_to_eat != -1 && all_ate_enough)
//         {
//             pthread_mutex_lock(&philos->dead_lock);
//             philos->dead_flag = 1;
//             pthread_mutex_unlock(&philos->dead_lock);
//             break;
//         }
//         usleep(1000);
//     }
// }
int check_philosopher_died(t_philosophers *philos, int i, size_t current_time)
{
    if (!philos->philos[i].eating && 
        (current_time - philos->philos[i].last_meal) >= philos->time_to_die)
    {
        pthread_mutex_lock(&philos->dead_lock);
        if (!philos->dead_flag)
        {
            philos->dead_flag = 1;
            pthread_mutex_unlock(&philos->dead_lock);
            printf("%zu %d %s\n", current_time - philos->start_time,
                  philos->philos[i].id, "died");
            
            return (1);
        }
        pthread_mutex_unlock(&philos->dead_lock);
    }
    return (0);
}

int check_all_ate_enough(t_philosophers *philos)
{
    int i;
    int all_ate_enough;

    i = 0;
    all_ate_enough = 1;
    if (philos->num_times_to_eat == -1)
        return (0);
    while (i < philos->num_of_philos)
    {
        pthread_mutex_lock(&philos->meal_lock);
        if (philos->philos[i].meals_eaten < philos->num_times_to_eat)
        {
            all_ate_enough = 0;
            pthread_mutex_unlock(&philos->meal_lock);
            break ;
        }
        pthread_mutex_unlock(&philos->meal_lock);
        i++;
    }
    if (all_ate_enough)
    {
        pthread_mutex_lock(&philos->dead_lock);
        philos->dead_flag = 1;
        pthread_mutex_unlock(&philos->dead_lock);
    }
    return (all_ate_enough);
}


void monitor_simulation(t_philosophers *philos)
{
    int i;
    size_t current_time;
    
    while (1)
    {
        i = 0;
        while (i < philos->num_of_philos)
        {
            pthread_mutex_lock(&philos->meal_lock);
            current_time = get_time();
            if (check_philosopher_died(philos, i, current_time))
            {
                pthread_mutex_unlock(&philos->meal_lock);
                return ;
            }
            pthread_mutex_unlock(&philos->meal_lock);
            i++;
        }
        if (check_all_ate_enough(philos))
            break;
        usleep(1000);
    }
}
