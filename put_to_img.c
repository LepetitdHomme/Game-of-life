/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <camillesellier@live.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 23:06:32 by csellier          #+#    #+#             */
/*   Updated: 2017/04/09 01:20:31 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gol.h"

static int	in_marge(int x)
{
	if (x < SCR_W - MARGE && x >= MARGE)
		return (0);
	return (1);
}

static int	in_tab(t_env *env, int x, int y)
{
	int	x2;
	int	y2;

	x2 = ((SCR_W - 2 * MARGE) / env->tab_size);
	y2 = SCR_H / env->tab_size;
	if (((x - MARGE) / x2) >= 0 && ((x - MARGE) / x2) < env->tab_size)
		if ((y / y2) >= 0 && (y / y2) < env->tab_size)
			return (0);
	return (1);
}

static int	alive(t_env *env, int x, int y)
{
	int		x2;
	int		y2;

	x2 = ((SCR_W - 2 * MARGE) / env->tab_size);
	y2 = SCR_H / env->tab_size;
	if (env->tab[(x - MARGE) / x2][y / y2].n == 1)
		return (0);
	return (1);
}

int			put_to_img(t_env *e)
{
	char	*data;
	int		b, s, en, x, y, index;

	if (e == NULL)
		return (1);
	if ((data = mlx_get_data_addr(e->img, &b, &s, &en)) == NULL)
		return (1);
	x = 0;
	while (x < SCR_W)
	{
		y = 0;
		while (y < SCR_H)
		{
			index = (x * b / 8) + (y * s);
			if (in_marge(x) == 0 && in_tab(e, x, y) == 0 && alive(e, x, y) == 0)
			{
				data[index] = 255;
				data[index + 1] = 0;
				data[index + 2] = 255;
			}
			y++;
		}
		x++;
	}
	return (0);
}
