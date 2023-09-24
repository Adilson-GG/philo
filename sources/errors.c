/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:41:32 by agomes-g          #+#    #+#             */
/*   Updated: 2023/09/24 12:26:09 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	conv;

	i = 0;
	conv = 0;
	s = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i ++;
	if (nptr[i] != '-' && !(nptr[i] >= 48 && nptr[i] <= 57) && nptr[i] != '+')
		return (0);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -1;
		i ++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		conv = (conv * 10) + (nptr[i] - '0');
		i ++;
	}
	return (s * conv);
}

long	ft_atoi_long(const char *nptr)
{
	int		i;
	long	s;
	long	conv;

	i = 0;
	conv = 0;
	s = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i ++;
	if (nptr[i] != '-' && !(nptr[i] >= 48 && nptr[i] <= 57) && nptr[i] != '+')
		return (0);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -1;
		i ++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		conv = (conv * 10) + (nptr[i] - '0');
		i ++;
	}
	return (s * conv);
}

int	check_digits(char *av_i)
{
	int	i;

	i = 0;
	while (av_i[i])
	{
		if (av_i[i] < 0 && av_i[i] > 9)
			return (1);
		i ++;
	}
	return (0);
}

int	errors(int ac, char **av)
{
	int	i;
	
	if (ac < 5 || ac > 6)
		return (printf("Enter 4 or 5 args please : number_of_philosophers; time_to_die; time_to_eat; time_to_sleep; [number_of_times_each_philosopher_must_eat]\n"), 1);
	i = 1;
	while (i < ac)
	{
		if (check_digits(av[i]) == 1 || ft_atoi(av[i]) != ft_atoi_long(av[i]) || ft_atoi(av[i]) == 0)
			return (printf("Invalid args\n"), 1);
		if (ft_atoi(av[1]) < 2)
			return (printf("Invalid args\n"), 1);
		i ++;
	}
	return (0);
}