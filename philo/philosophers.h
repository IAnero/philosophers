/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrakot <marvin@time_last_meal  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:06:42 by herrakot          #+#    #+#             */
/*   Updated: 2025/02/08 19:01:00 by herrakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define NC "\e[0m"
# define YELLOW "\e[37m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

# define THINKING 0
# define EATING 2
# define SLEEP 3

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;
typedef struct s_philo
{
	t_mtx			fork;
	int				id;
	long			meal_count;
	t_mtx			mtx_meal;
	long			time_last_meal;
	long			time_last_meal_by_monitor;
	bool			is_maxmeal_reached;
	pthread_t		thread;
	int				state;
	t_data			*info;
	bool			has_fork;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_time_eat;
	long	nbr_eat_zero;
	long	time_to_start;
	long	start_simulation;
	bool	end_simulation;
	t_mtx	mtx_info;
	t_philo	*philo;
}	t_data;

void	ft_error_arg(char *av[]);
void	ft_errorvalidity_arg(char *av[]);

int		ft_is_in(char c, char *s);
int		ft_is_numeric(char *s);
long	ft_atol(const char *str);
void	ft_mtx_destroy(t_philo *p);
long	get_time(void);
long	get_time_simulation(long time);
bool	ft_print(t_philo *philo, char *str, char *color);
void	my_usleep(t_philo *p, int time);
void	fork_lock(t_philo *philo);
long	mtx_get_last_meal(t_philo *p);

int		check_validity_arg(char **str);
void	init_data_routine(char *av[], t_data *info);

void	struct_init(t_data *info);
void	add_back(t_philo **p, t_philo *new_p);
t_philo	*init_philos(int id, t_data *info);
t_philo	*init_table(t_data *info);
void	create(t_data *info, t_philo *p);

void	*philo_routine(void *arg);
bool	eat(t_philo *p);
bool	slep(t_philo *p);
bool	think(t_philo *p);
void	*monitor(void *arg);
bool	is_dead(t_philo *p);
void	*is_alone(t_philo *p);
bool	is_stop(t_philo *p);
void	fork_unlock(t_philo *philo);
bool	check_all_philosophers_meals(t_philo *p);
bool	check_meal_count(t_philo *p);
bool	die_engine(t_philo *p, long total_time);
long	time_assignation(t_philo *p);

#endif