/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:44:07 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/18 09:34:59 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
    t_philosophers  philos;

	if (ac == 6 || ac == 5)
    {
        if (!parse_philos(&philos, av))
        {
            printf("Error: Invalid arguments\n");
            return (1);
        }
        if (!init_philosophers(&philos))
        {
            printf("Error: Failed to initialize philosophers\n");
            return (1);
        }
        if (!start_simulation(&philos))
        {
            printf("Error: Failed to start simulation\n");
            return (1);
        }
        monitor_simulation(&philos);
        cleanup_resources(&philos);
        return (0);
    }
    printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
    return (1);
}
