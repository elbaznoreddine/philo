/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:23:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/24 11:32:56 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_resources(t_philosophers *philosophers, int free_philo, int need_k)
{
	int	i;
	int	status;

	i = -1;
	if (need_k)
	{
		while (++i < philosophers->num_of_philos)
		{
			waitpid(-1, &status, 0);
			if (status != 0)
			{
				i = -1;
				while (++i < philosophers->num_of_philos)
					kill(philosophers->philos[i], SIGKILL);
				break;
			}
		}
	}
	if (philosophers->philos && free_philo)
		free(philosophers->philos);
	if (philosophers->meal_lock && philosophers->meal_lock != SEM_FAILED)
		sem_close(philosophers->meal_lock);
	if (philosophers->write_lock && philosophers->write_lock != SEM_FAILED)
		sem_close(philosophers->write_lock);
	if (philosophers->forks && philosophers->forks != SEM_FAILED)
		sem_close(philosophers->forks);
	sem_unlink("/meal_lock");
	sem_unlink("/write_lock");
	sem_unlink("/forks");
}
