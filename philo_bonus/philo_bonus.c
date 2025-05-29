/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:44:07 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/30 16:16:31 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_puterror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
}

void	exit_philosophers(char *message, int free_philos,
	t_philosophers *philosophers, int need_k)
{
	if (message)
		printf("%s\n", message);
	cleanup_resources(philosophers, free_philos, need_k);
	exit(1);
}

int	main(int ac, char **av)
{
	t_philosophers	philosophers;

	if (ac == 6 || ac == 5)
	{
		if (!parse_philos(&philosophers, av))
		{
			exit_philosophers("Error: Invalid arguments\n",
				1, &philosophers, 0);
		}
		if (!init_philosophers(&philosophers))
		{
			exit_philosophers("Error: Failed to initialize philosophers\n",
				1, &philosophers, 0);
		}
		cleanup_resources(&philosophers, 1, 1);
		return (0);
	}
	ft_puterror("Error: Wrong number of argument\n");
	return (1);
}
