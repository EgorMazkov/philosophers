/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_eat_sleep_waiting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:37:05 by ghumbert          #+#    #+#             */
/*   Updated: 2021/11/03 19:44:49 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*l_r_fork(void *a)
{
	t_phils	*phils;

	phils = (t_phils *)a;
	if (phils->index % 2)
	{
		pthread_mutex_lock(phils->left_fork);
		printf_phil(phils, LEFT_FORK);
		pthread_mutex_lock(phils->right_fork);
		printf_phil(phils, RIGHT_FORK);
	}
	else
	{
		pthread_mutex_lock(phils->right_fork);
		printf_phil(phils, RIGHT_FORK);
		pthread_mutex_lock(phils->left_fork);
		printf_phil(phils, LEFT_FORK);
	}
	phils->check = FALSE;
	return (NULL);
}

_Bool	check_fork(t_phils *phils)
{
	pthread_t	thread_t;

	if (phils->hil->dead)
		return (FALSE);
	phils->check = TRUE;
	usleep(100);
	pthread_create(&thread_t, NULL, l_r_fork, phils);
	if (phils->check)
		printf_phil(phils, WAITING);
	while (phils->check)
	{
		if (phils->hil->dead)
			return (FALSE);
		if (get_time() - phils->last_eat >= phils->hil->lifetime)
		{
			phils->hil->dead = 1;
			printf_phil(phils, DEAD);
			return (FALSE);
		}
		usleep(75);
	}
	return (TRUE);
}

_Bool	eat(long long sleep, long long *gettime, t_phils *phils)
{
	long long	lst_eat;

	lst_eat = phils->last_eat;
	phils->last_eat = get_time();
	if (phils->hil->dead == 1)
		return (FALSE);
	if (((*gettime - lst_eat) + phils->hil->time_of_reception_write) < \
	phils->hil->lifetime)
		usleep((phils->hil->time_of_reception_write - 15) * 1000);
	while (sleep > *gettime)
	{
		usleep(331);
		if (*gettime - phils->last_eat > phils->hil->lifetime || \
		phils->hil->amount_of_food_intake == 0)
		{
			phils->hil->dead = 1;
			printf_phil(phils, DEAD);
			return (FALSE);
		}
		*gettime = get_time();
	}
	printf_phil(phils, EAT);
	if (phils->hil->amount_of_food_intake)
		phils->amount_of_food++;
	return (TRUE);
}

_Bool	sleeps(long long sleep, long long *gettime, t_phils *phils)
{
	*gettime = get_time();
	if (phils->hil->dead == 1)
		return (FALSE);
	if (*gettime - phils->last_eat >= phils->hil->lifetime)
	{
		phils->hil->dead = 1;
		printf_phil(phils, DEAD);
		return (FALSE);
	}
	printf_phil(phils, SLEEP);
	while (sleep > *gettime)
	{
		if (phils->hil->dead)
			return (FALSE);
		if (*gettime - phils->last_eat >= phils->hil->lifetime)
		{
			phils->hil->dead = 1;
			printf_phil(phils, DEAD);
			return (FALSE);
		}
		usleep(331);
		*gettime = get_time();
	}
	return (TRUE);
}

_Bool	check_sleep(t_phils *phils, short alf)
{
	long long	sleep;
	long long	gettime;

	gettime = get_time();
	sleep = sleep_check(phils, alf) + gettime;
	if (alf == EAT)
		eat(sleep, &gettime, phils);
	if (alf == SLEEP)
		sleeps(sleep, &gettime, phils);
	return (TRUE);
}
