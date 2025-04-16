/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:44:07 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/16 15:15:58 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_puterror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
}

int	main(int ac, char **av)
{
	t_philosophers	philosophers;

	if (ac == 6 || ac == 5)
	{
		if (!parse_philos(&philosophers, av))
		{
			ft_puterror("Error: Invalid arguments\n");
			return (1);
		}
		if (!init_philosophers(&philosophers))
		{
			ft_puterror("Error: Failed to initialize philosophers\n");
			return (1);
		}
		if (!start_simulation(&philosophers))
		{
			cleanup_error(&philosophers);
			ft_puterror("Error: Failed to start simulation\n");
			return (1);
		}
		if (!cleanup_resources(&philosophers))
			return (ft_puterror("Error: join problem\n"), 1);
		return (0);
	}
	return (ft_puterror("Error: Wrong number of argument\n"), 1);
}
