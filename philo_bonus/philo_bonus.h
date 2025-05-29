/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:44:03 by noel-baz          #+#    #+#             */
/*   Updated: 2025/04/22 23:06:29 by noel-baz         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

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
void	*superviseur(t_philosophers *philosophers);
int		is_simulation_over(t_philosophers *philosophers);
void	print_status(t_philosophers *philo, char *status);
void	*philosopher_routine(t_philosophers	*philosophers);
int		start_simulation(t_philosophers *philosophers);
void	monitor_simulation(t_philosophers *philosophers);
void	philo_eat(t_philosophers *philosophers);
void	philo_take(t_philosophers *philosophers);
void	philo_sleep(t_philosophers *philosophers);
void	handle_one_philo(t_philosophers *philosophers);
void	cleanup_resources(t_philosophers *philosophers, int free_philo,
			int need_k);
void	exit_philosophers(char *message, int free_philos,
			t_philosophers *philosophers, int need_k);
int		ft_usleep(size_t milliseconds);
long	ft_atoi(const char *str);
#endif