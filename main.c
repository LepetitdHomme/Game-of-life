/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <camillesellier@live.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 23:59:42 by csellier          #+#    #+#             */
/*   Updated: 2017/04/09 02:18:06 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gol.h"

static t_env	*init_env(int x)
{
	t_env	*env;

	if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	if ((env->scr = mlx_init()) == NULL)
		return (NULL);
	if ((env->win = mlx_new_window(env->scr, SCR_W, SCR_H, "GOL")) == NULL)
		return (NULL);
	env->tab = NULL;
	env->tab_size = x;
	env->img = NULL;
	return (env);
}

static int		free_tab(t_env *env)
{
	int		i;

	if (env == NULL || env->tab == NULL)
		return (0);
	i = 0;
	while (i < env->tab_size)
	{
		free(env->tab[i]);
		i++;
	}
	free(env->tab);
	env->tab = NULL;
	return (0);
}

static int		init_tab(t_env *v)
{
	int		x;
	int		y;
	int		i;

	if (v == NULL)
		return (1);
	if (v->tab != NULL)
		free_tab(v);
	if ((v->tab = (t_cell **)malloc(sizeof(t_cell) * v->tab_size)) == NULL)
		return (1);
	for (i = 0; i < v->tab_size ; i++)
	{
		if ((v->tab[i] = (t_cell *)malloc(sizeof(t_cell) * v->tab_size)) == NULL)
			return (1);
	}
	x = 0;
	while (x < v->tab_size)
	{
		y = 0;
		while (y < v->tab_size)
		{
			if (x == 3 && y == 2)
				v->tab[x][y].n = 1;
			else if (x == 4 && y == 3)
				v->tab[x][y].n = 1;
			else if ((x == 2 || x == 3 || x == 4) && y == 4)
				v->tab[x][y].n = 1;
			else
				v->tab[x][y].n = 0;
			v->tab[x][y].n_1 = 0;
			v->tab[x][y].age = 0;
			y++;
		}
		x++;
	}
	return (0);
}

static int		init_expose(t_env *env)
{
	if (env == NULL)
		return (1);
	if (env->img != NULL)
		mlx_destroy_image(env->scr, env->img);
	if ((env->img = mlx_new_image(env->scr, SCR_W, SCR_H)) == NULL)
		return (1);
	put_to_img(env);
	mlx_put_image_to_window(env->scr, env->win, env->img, 0, 0);
	return (0);
}

static int		expose(t_env *env)
{
	static int	i = 0;
	if (env == NULL)
		return (1);
	i++;
	if (i < 300000)
		return (0);
	else
		i = 0;
	if (env->img != NULL)
		mlx_destroy_image(env->scr, env->img);
	if ((env->img = mlx_new_image(env->scr, SCR_W, SCR_H)) == NULL)
		return (1);
	seed(env);
	reset_seed(env);
	put_to_img(env);
	mlx_put_image_to_window(env->scr, env->win, env->img, 0, 0);
	return (0);
}

static int		reset(t_env *env)
{
	init_tab(env);
	init_expose(env);
	return (0);
}

static int		key_press(int key, t_env *env)
{
	printf("%d = key\n", key);
	if (key == SPACE)
		reset(env);
	if (key == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int				main(int ar, char **av)
{
	t_env	*env;

	(void)ar;
	(void)av;
	if ((env = init_env(100)) == NULL)
		return (1);
	if (init_tab(env) != 0)
		return (1);
	if (init_expose(env) != 0)
		return (1);
	mlx_hook(env->win, 2, 1L << 0, key_press, env);
	mlx_loop_hook(env->scr, expose, env);
	mlx_loop(env->scr);
	return (0);
}
