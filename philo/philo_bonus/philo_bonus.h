/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:44:03 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/23 15:42:38 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct philosophers
{
	pthread_t		thread_monitor;
	int				id;
	sem_t			*meal_lock;
	sem_t			*write_lock;
	sem_t			*forks;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_philos;
	int				num_times_to_eat;
	size_t			start_time;
	size_t			last_meal;
	int				meals_eaten;
	int				*philos;
}					t_philosophers;

int		parse_philos(t_philosophers *philosophers, char **av);
int		init_philosophers(t_philosophers	*philosophers);
int		init_threads(t_philosophers *philosophers);
size_t	get_time(void);
void	*superviseur(void	*arg);
int		is_simulation_over(t_philosophers *philosophers);
void	print_status(t_philosophers *philo, char *status);
void	*philosopher_routine(void *arg);
int		start_simulation(t_philosophers *philosophers);
void	monitor_simulation(t_philosophers *philosophers);
void	philo_eat(t_philosophers *philo);
void	handle_one_philo(t_philosophers *philosophers);
void	cleanup_resources(t_philosophers *philosophers);
int		ft_usleep(size_t milliseconds);
long	ft_atoi(const char *str);
#endif