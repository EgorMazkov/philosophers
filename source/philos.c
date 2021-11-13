/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:05:49 by ghumbert          #+#    #+#             */
/*   Updated: 2021/11/03 20:02:02 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_sleep_eat(short alf, t_phils *phils)
{
	if (alf == EAT)
		return (phils->hil->time_of_reception_write);
	if (alf == SLEEP)
		return (phils->hil->food_intake);
	return (0);
}

int	check_eat(t_phils *phils)
{
	t_phils	*dest;
	int		num_philo;

	dest = phils;
	num_philo = dest->hil->number_of_filo;
	while (num_philo)
	{
		if (dest->amount_of_food < dest->hil->amount_of_food_intake)
			return (0);
		dest = dest->right_phil;
		num_philo--;
	}
	if (!num_philo)
	{
		dest->hil->check_eat = 1;
		return (1);
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[++i])
	{
		while (argv[i][j])
		{
			if (!ft_strchr("0123456789 \n+", argv[i][j]))
				return (1);
			j++;
		}
		j = 0;
	}
	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_atoi(argv[++i]) < 1)
		return (1);
	if (ft_atoi(argv[i]) > 200)
		return (1);
	if (ft_atoi(argv[++i]) < 60)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_phils	*phils;
	t_dest	philo;
	int		num_fil;

	if (check_arg(argc, argv))
	{
		printf("Error\n");
		return (1);
	}
	num_fil = ft_atoi(argv[1]);
	phils = NULL;
	null_struct_dest(&philo, argv);
	list_start_end(&phils, &philo, num_fil);
	num_fil = ft_atoi(argv[1]);
	creating_streams(&phils, num_fil);
	while (!philo.dead)
	{
		usleep(1000);
		if (philo.check_eat)
			return (0);
	}
	return (0);
}
