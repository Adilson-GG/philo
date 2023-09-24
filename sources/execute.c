/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:44:43 by agomes-g          #+#    #+#             */
/*   Updated: 2023/09/24 13:31:54 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*philo(t_data *data)
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
	}
	return (philo);
}

void	free_forks(pthread_mutex_t *forks, t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j <= i)
		pthread_mutex_destroy(&forks[i]);
	if (j >= 0 && j != data->num_philo)
		printf("Can't init forks");
	free(forks);
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

int	init_threads(pthread_t *philosophers, t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_create(&philosophers[i], NULL, start, &(philo[i])) != 0)
			return (1);
	}
}
void	wait_thread(t_data *data, pthread_mutex_t *forks, pthread_t *philosophers)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_join(philosophers[i], NULL);
}

int	execute(t_data *data, pthread_mutex_t *forks, pthread_t *philosophers)
{
	t_philo	*philo;
	
	philo = init_philo(data);
	if (!philo)
	{
		printf("Can't init philosophers");
		return (free_all(data, forks, -1), 1);
	}
	if (init_forks(forks, data))
		return (1);
	if (init_threads(philosophers, data, philo))
	{
		printf("Can't create philosophers's threads");
		return (free_all(data, forks, data->num_philo -1), 1);
	}
	wait_thread(data, forks, philosophers);
	return (0);
}
