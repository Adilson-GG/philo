/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 09:01:36 by agomes-g          #+#    #+#             */
/*   Updated: 2023/09/26 11:57:24 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_data *data, pthread_mutex_t *forks, int i)//, pthread_t *philosophers)
{
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
	if (forks)
		free_forks(forks, data, i);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int i;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->num_philo)
	{
		philo[i].last_meal = 0;
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->num_philo;
		philo[i].meal_ate = 0;
		philo[i].dead = 0;
	}
	return (philo);
}

int	init_forks(pthread_mutex_t *forks, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (free_forks(forks, data, i), 1);
	}
	return (0);
}
int	init_threads(pthread_t *philosophers, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_create(&philosophers[i], NULL, start, data) != 0)
			return (1);
	}
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->all_ate_x_time = 0;
	if (ac == 6)
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
	data->philo = init_philo(data);
	return (data);
}
