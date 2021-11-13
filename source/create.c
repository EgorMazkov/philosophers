/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:42:24 by ghumbert          #+#    #+#             */
/*   Updated: 2021/11/03 19:44:56 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

_Bool	creating_streams(t_phils **phils, int num_fil)
{
	t_phils	*dest;

	dest = *phils;
	pthread_mutex_lock(&(*phils)->hil->mutex_start_pthread);
	pthread_mutex_lock(&(*phils)->hil->mutex_odd);
	while (num_fil)
	{
		pthread_create(&dest->thread_t, NULL, lite, dest);
		num_fil--;
		dest = dest->right_phil;
	}
	pthread_mutex_unlock(&(*phils)->hil->mutex_start_pthread);
	usleep(4000 / 200 * dest->hil->number_of_filo);
	pthread_mutex_unlock(&(*phils)->hil->mutex_odd);
	return (TRUE);
}

void	*lite(void *a)
{
	t_phils	*phil;

	phil = (t_phils *)a;
	phil->last_eat = get_time();
	while (TRUE)
	{
		if (!check_fork(phil))
			return (NULL);
		if (!check_sleep(phil, EAT))
			return (NULL);
		if (!phil->hil->dead)
		{
			pthread_mutex_unlock(phil->right_fork);
			pthread_mutex_unlock(phil->left_fork);
		}
		if (!check_sleep(phil, SLEEP))
			return (NULL);
		if (phil->hil->amount_of_food_intake != -1 && check_eat(phil))
		{
			pthread_join(phil->thread_t, NULL);
			return (NULL);
		}
	}
	return (NULL);
}

long long	sleep_check(t_phils *phils, short alf)
{
	if (alf == SLEEP)
		return (phils->hil->food_intake);
	if (alf == EAT)
		return (phils->hil->time_of_reception_write);
	return (0);
}
