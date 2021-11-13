/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:56:34 by ghumbert          #+#    #+#             */
/*   Updated: 2021/11/03 19:55:59 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# define EAT 10
# define TRUE 1
# define DEAD -1
# define FALSE 0
# define SLEEP 20
# define WAITING 50
# define LEFT_FORK 100
# define RIGHT_FORK 200

typedef struct s_dest
{
	int				num;
	int				number_of_filo;
	int				lifetime;
	int				time_of_reception_write;
	int				food_intake;
	int				amount_of_food_intake;
	char			**argv;
	long long		time;
	pthread_mutex_t	mutex_start_pthread;
	pthread_mutex_t	mutex_odd;
	pthread_mutex_t	mutex_printf;
	int				dead;
	int				check_eat;
	_Bool			check;
}	t_dest;

typedef struct s_phils
{
	int				index;
	int				life;
	int				amount_of_food;
	_Bool			check;
	t_dest			*hil;
	long long		last_eat;
	long long		timefork;
	pthread_t		thread_t;
	struct s_phils	*left_phil;
	struct s_phils	*right_phil;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_phils;

int			check_philo(t_dest *el, int num_fil);
int			check_sleep_eat(short alf, t_phils *phils);
int			check_eat(t_phils *phils);
int			check_arg(int argc, char **argv);
int			ft_atoi(const char *str);
char		*ft_strchr(const char *s, int c);
void		printf_phil(t_phils *phils, short alf);
void		lst_add(t_phils **lst, t_phils *el);
void		list_start_end(t_phils **phils, t_dest *philo, int num_fil);
void		null_struct_dest(t_dest *philo, char **argv);
void		*lite(void *a);
void		lst_free_all(t_phils **lst);
void		*l_r_fork(void *a);
_Bool		creating_streams(t_phils **phils, int num_fil);
_Bool		check_fork(t_phils *phils);
_Bool		eat(long long sleep, long long *gettime, t_phils *phils);
_Bool		sleeps(long long sleep, long long *gettime, t_phils *phils);
_Bool		check_sleep(t_phils *phils, short alf);
t_phils		*new_cmd(t_dest *philo_argv, int num_fil);
long long	get_time(void);
long long	sleep_check(t_phils *phils, short alf);

#endif
