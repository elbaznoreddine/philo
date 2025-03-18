/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:40:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/18 14:41:45 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
static int	is_digit(char c)
{
	return (c <= '9' && c >= '0');
}

long	ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	j = i;
	while (str[j])
	{
		if (!is_digit(str[j]))
			return (0);
		j++;
	}
	while (str[i] && (str[i] <= '9' && str[i] >= '0'))
	{
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && result * sign < INT_MIN))
			return (LONG_MAX);
		i++;
	}
	return (result * sign);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_usleep(size_t milliseconds)
{
    size_t start;

    start = get_time();
    while ((get_time() - start) < milliseconds)
        usleep(500);
    return (0);
}