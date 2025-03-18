/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:23:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/18 13:54:54 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_resources(t_philosophers *philos)
{
    int i;
    
    i = 0;
    while (i < philos->num_of_philos)
    {
        pthread_join(philos->philos[i].thread, NULL);
        i++;
    }
    i = 0;
    while (i < philos->num_of_philos)
    {
        pthread_mutex_destroy(&philos->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&philos->dead_lock);
    pthread_mutex_destroy(&philos->meal_lock);
    pthread_mutex_destroy(&philos->write_lock);
    free(philos->forks);
    free(philos->philos);
}