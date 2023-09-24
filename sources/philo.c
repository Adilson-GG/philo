/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:56:31 by agomes-g          #+#    #+#             */
/*   Updated: 2023/09/24 13:16:46 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	if (ac == 6)
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
	return (data);
}

void	free_all(t_data *data, pthread_mutex_t *forks, int i)//, pthread_t *philosophers)
{
	if (data)
		free(data);
	if (forks)
		free_forks(forks, data, i);
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
