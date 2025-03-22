/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:44:03 by noel-baz          #+#    #+#             */
/*   Updated: 2025/03/21 06:46:45 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libc.h>
# include <pthread.h>

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
	struct philo	*philos;
}					t_philosophers;

typedef struct philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_philosophers	*shared;
}					t_philo;

int		parse_philos(t_philosophers *philos, char **av);
int		init_philosophers(t_philosophers	*philos);
int		init_threads(t_philosophers *philos);
size_t	get_time(void);
int		is_simulation_over(t_philosophers *philos);
void	print_status(t_philo *philo, char *status);
void	*philosopher_routine(void *arg);
int		start_simulation(t_philosophers *philos);
void	monitor_simulation(t_philosophers *philos);
void	philo_eat(t_philo *philo);
void	handle_one_philo(t_philosophers *philos);
void	cleanup_resources(t_philosophers *philos);
int ft_usleep(size_t milliseconds);
long	ft_atoi(const char *str);
# endif
