/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:19:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/16 18:32:54 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *philosopher_routine(t_philosophers *philosophers)
{
    size_t current;
    while (1)
    {
        // Check for starvation
        sem_wait(philosophers->meal_lock);
        current = get_time();
        if (current - philosophers->last_meal > philosophers->time_to_die)
        {
            sem_wait(philosophers->write_lock);
            printf("%zu %d %s\n", get_time() - philosophers->start_time, philosophers->id, "died");
            sem_post(philosophers->write_lock);
            sem_post(philosophers->meal_lock);
            exit(1);
        }
        // Check if meal limit reached
        if (philosophers->num_times_to_eat != -1
            && philosophers->meals_eaten >= philosophers->num_times_to_eat)
        {
            sem_post(philosophers->meal_lock);
            exit(0);
        }
        sem_post(philosophers->meal_lock);

        // Perform philosopher actions
        philo_take(philosophers);
        philo_eat(philosophers);
        philo_sleep(philosophers);
        usleep(100); 
    }
    return (NULL);
}

void	handle_one_philo(t_philosophers *philosophers)
{
	printf("%zu %d %s\n", get_time() - philosophers->start_time, 1,
		"has taken a fork");
	ft_usleep(philosophers->time_to_die);
	printf("%zu %d %s\n", get_time() - philosophers->start_time, 1, "die");
	exit(0);
}

// void	*superviseur(void	*arg)
// {
// 	t_philosophers	*philosophers;
// 	// size_t			last_meal;
// 	size_t			current;
// 	// int				meal;

// 	philosophers = (t_philosophers*) arg;
// 	while (1)
// 	{
// 		// exit(0);
// 		sem_wait(philosophers->meal_lock);
// 		current = get_time();
// 		if (current - philosophers->last_meal > philosophers->time_to_die)
// 		{
// 			sem_wait(philosophers->write_lock);
// 			printf("%zu %d %s\n", get_time() - philosophers->start_time, philosophers->id, "died");
// 			sem_post(philosophers->write_lock);
// 			sem_post(philosophers->meal_lock);
// 			exit(1);
// 		}
// 		if (philosophers->num_times_to_eat != -1
// 			&& (philosophers->meals_eaten >= philosophers->num_times_to_eat))
// 		{
// 			sem_post(philosophers->meal_lock);
// 			exit(0);
// 		}
// 		sem_post(philosophers->meal_lock);
// 		usleep(100);
// 	}
// 	return (NULL);
// }
