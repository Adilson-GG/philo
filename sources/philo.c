/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:56:31 by agomes-g          #+#    #+#             */
/*   Updated: 2023/09/26 11:39:05 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	wait_thread(t_data *data, pthread_t *philosophers)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_join(philosophers[i], NULL);
}

int	execute(t_data *data, pthread_mutex_t *forks, pthread_t *philosophers)
{
//	t_philo	*philo;
	
//	philo = init_philo(data);
	if (!(data->philo))
	{
		printf("Can't init philosophers");
		return (free_all(data, forks, -1), 1);
	}
	if (init_forks(forks, data))
		return (1);
	if (init_threads(philosophers, data, data->philo))
	{
		printf("Can't create philosophers's threads");
		return (free_all(data, forks, data->num_philo -1), 1);
	}
	wait_thread(data, philosophers);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
	
	if (errors(argc, argv))
		return (0);
	data = init_data(argc, argv);
	if (!data)
		return (printf("Problem with malloc\n"), 0);
	forks = (pthread_mutex_t *)malloc(data->num_meal * sizeof(pthread_mutex_t));
	if (!forks)
		return (printf("Problem with malloc\n"), free_all(data, forks, -1), 0);
	philosophers = (pthread_t *)malloc(data->num_meal * sizeof(pthread_t));
	if (!philosophers)
		return (printf("Problem with malloc\n"), free_all(data, forks, -1), 0);
	if (execute(data, forks, philosophers) == 0)
		free_all(data, forks, data->num_philo - 1);
	return (0);
}
