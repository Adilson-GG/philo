/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:54:47 by agomes-g          #+#    #+#             */
/*   Updated: 2023/09/26 11:58:56 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef	struct s_philo
{
	int		id;
	long	last_meal;
	int		meal_ate;
	int		left_fork;
	int		right_fork;
	int		dead;
}	t_philo;

typedef struct s_data
{
	int 	num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_meal;
	int		all_ate_x_time;
	t_philo	*philo;
}	t_data;

void	free_forks(pthread_mutex_t *forks, t_data *data, int i);
void	free_all(t_data *data, pthread_mutex_t *forks, int i);

int		execute(t_data *data, pthread_mutex_t *forks, pthread_t *philosophers);
void	*start(void *arg);

t_philo	*init_philo(t_data *data);
t_data	*init_data(int ac, char **av);
int		init_forks(pthread_mutex_t *forks, t_data *data);
int		init_threads(pthread_t *philosophers, t_data *data);

int		errors(int ac, char **av);
int		check_digits(char *av_i);
int		ft_atoi(const char *nptr);
long	ft_atoi_long(const char *nptr);

#endif