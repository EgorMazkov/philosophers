/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:43:39 by ghumbert          #+#    #+#             */
/*   Updated: 2021/11/03 19:55:44 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	printf_phil(t_phils *phils, short alf)
{
	long	ms;

	ms = get_time() - phils->hil->time;
	pthread_mutex_lock(&phils->hil->mutex_printf);
	if (alf == LEFT_FORK)
		printf("\033[0;35m%ld: %d left_fork\n", ms, phils->index);
	else if (alf == RIGHT_FORK)
		printf("\033[0;35m%ld: %d right_fork\n", ms, phils->index);
	else if (alf == DEAD)
		printf("\033[0;31m%ld: %d dead\n", ms, phils->index);
	else if (alf == WAITING)
		printf("\033[0;37m%ld: %d waiting\n", ms, phils->index);
	else if (alf == SLEEP)
		printf("\033[0;33m%ld: %d sleep\n", ms, phils->index);
	else if (alf == EAT)
		printf("\033[0;36m%ld: %d eat\n", ms, phils->index);
	if (alf != DEAD)
		pthread_mutex_unlock(&phils->hil->mutex_printf);
}

long long	get_time(void)
{
	struct timeval	a;

	gettimeofday(&a, NULL);
	return ((a.tv_sec * 1000000 + a.tv_usec) / 1000);
}

int	check_philo(t_dest *el, int num_fil)
{
	num_fil--;
	return (el->num++);
}

void	null_struct_dest(t_dest *philo, char **argv)
{
	philo->food_intake = ft_atoi(argv[4]);
	philo->lifetime = ft_atoi(argv[2]);
	philo->number_of_filo = ft_atoi(argv[1]);
	philo->time_of_reception_write = ft_atoi(argv[3]);
	philo->num = 0;
	if (argv[5])
		philo->amount_of_food_intake = ft_atoi(argv[5]);
	else
		philo->amount_of_food_intake = -1;
	philo->argv = argv;
	pthread_mutex_init(&philo->mutex_printf, NULL);
	pthread_mutex_init(&philo->mutex_start_pthread, NULL);
	pthread_mutex_init(&philo->mutex_odd, NULL);
	philo->dead = 0;
	philo->time = get_time();
	philo->check_eat = 0;
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}
