/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seed.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <camillesellier@live.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 01:18:03 by csellier          #+#    #+#             */
/*   Updated: 2017/04/09 02:18:05 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gol.h"

static int	in_tab(t_env *env, int x, int y)
{
	if (x >= 0 && x < env->tab_size && y >= 0 && y < env->tab_size)
		return (0);
	return (1);
}

static int	count_neighbour(t_env *env, int x, int y)
{
	int		count;

	if (env == NULL || env->tab == NULL)
		return (-1);
	count = 0;
	if (in_tab(env, x - 1, y - 1) == 0  && env->tab[x - 1][y - 1].n == 1)
		count++;
	if (in_tab(env, x, y - 1) == 0 && env->tab[x][y - 1].n == 1)
		count++;
	if (in_tab(env, x + 1, y - 1) == 0 && env->tab[x + 1][y - 1].n == 1)
		count++;
	if (in_tab(env, x - 1, y) == 0 && env->tab[x - 1][y].n == 1)
		count++;
	if (in_tab(env, x + 1, y) == 0 && env->tab[x + 1][y].n == 1)
		count++;
	if (in_tab(env, x - 1, y + 1) == 0 && env->tab[x - 1][y + 1].n == 1)
		count++;
	if (in_tab(env, x, y + 1) == 0 && env->tab[x][y + 1].n == 1)
		count++;
	if (in_tab(env, x + 1, y + 1) == 0 && env->tab[x + 1][y + 1].n == 1)
		count++;
	return (count);
}

int			reset_seed(t_env *env)
{
	int		x;
	int		y;

	if (env == NULL || env->tab == NULL)
		return (1);
	for (x = 0 ; x < env->tab_size ; x++)
	{
		for(y = 0 ; y < env->tab_size ; y++)
		{
			env->tab[x][y].n = env->tab[x][y].n_1;
			env->tab[x][y].n_1 = 0;
		}
	}
	return (0);
}

int			seed(t_env *env)
{
	int		x;
	int		y;
	int		count;

	for (x = 0 ; x < env->tab_size ; x++)
	{
		for (y = 0 ; y < env->tab_size ; y++)
		{
			if ((count = count_neighbour(env, x, y)) == -1)
				return (1);
			if (env->tab[x][y].n == 1)
				env->tab[x][y].n_1 = (count == 2 || count == 3) ? 1 : 0;
			else
				env->tab[x][y].n_1 = (count == 3) ? 1 : 0;
		}
	}
	return (0);
}
