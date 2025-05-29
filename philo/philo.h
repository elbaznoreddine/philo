/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:44:03 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/30 16:00:29 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct philosophers
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_philos;
	int				num_times_to_eat;
	size_t			start_time;
	struct philo	*philo;
}					t_philosophers;

typedef struct philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_philosophers	*shared;
}					t_philo;

int		parse_philos(t_philosophers *philosophers, char **av);
int		init_philosophers(t_philosophers	*philos);
int		init_threads(t_philosophers *philosophers);
size_t	get_time(void);
int		is_simulation_over(t_philosophers *philosophers);
void	print_status(t_philo *philo, char *status);
void	*philosopher_routine(void *arg);
int		start_simulation(t_philosophers *philosophers);
void	monitor_simulation(t_philosophers *philosophers);
void	philo_eat(t_philo *philo);
int		check_philosopher_died(t_philosophers *philosophers, int i);
int		check_all_ate_enough(t_philosophers *philosopher);
void	handle_one_philo(t_philosophers *philosophers);
int		cleanup_resources(t_philosophers *philosophers);
void	ft_usleep(size_t milliseconds, t_philosophers *philosophers);
long	ft_atoi(const char *str);
void	cleanup_error(t_philosophers *philosophers);
int		create_thread(t_philosophers *philosophers);
#endif