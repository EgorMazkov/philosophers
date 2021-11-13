/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:40:40 by ghumbert          #+#    #+#             */
/*   Updated: 2021/11/03 19:43:08 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	lst_free_all(t_phils **lst)
{
	t_phils	*tmp;
	t_phils	*tmp2;
	t_dest	*data;
	int		len;

	tmp = *lst;
	data = tmp->hil;
	if (!tmp)
		return ;
	while (tmp->index > tmp->left_phil->index)
		tmp = tmp->left_phil;
	len = (tmp2 = tmp)->hil->number_of_filo;
	while (len--)
	{
		free(tmp2->right_phil);
		pthread_detach(tmp2->thread_t);
		tmp2 = tmp2->right_phil;
	}
	pthread_mutex_destroy(&data->mutex_start_pthread);
	pthread_mutex_destroy(&data->mutex_printf);
	pthread_mutex_destroy(&data->mutex_odd);
}

void	list_start_end(t_phils **phils, t_dest *philo, int num_fil)
{
	int		num_ac;
	t_phils	*st;
	t_phils	*end;

	st = NULL;
	num_ac = 0;
	num_ac = ft_atoi(philo->argv[1]);
	while (num_ac)
	{
		lst_add(phils, new_cmd(philo, num_fil));
		num_ac--;
	}
	end = *phils;
	while ((*phils)->left_phil)
		*phils = (*phils)->left_phil;
	(*phils)->left_phil = end;
	end->right_phil = *phils;
	end->right_fork = (*phils)->left_fork;
}

t_phils	*new_cmd(t_dest *philo_argv, int num_fil)
{
	t_phils	*el;
	int		j;

	j = 0;
	el = (t_phils *)malloc(sizeof(t_phils));
	if (!el)
		return (NULL);
	el->index = check_philo(philo_argv, num_fil);
	el->left_fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(el->left_fork, NULL);
	el->right_fork = NULL;
	el->left_phil = NULL;
	el->right_phil = NULL;
	el->check = TRUE;
	el->hil = philo_argv;
	el->amount_of_food = 0;
	return (el);
}

void	lst_add(t_phils **lst, t_phils *el)
{
	if (!el)
		return ;
	if (!*lst)
	{
		*lst = el;
		return ;
	}
	el->left_phil = *lst;
	(*lst)->right_phil = el;
	(*lst)->right_fork = el->left_fork;
	*lst = el;
}
