/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gol.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <camillesellier@live.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 22:46:33 by csellier          #+#    #+#             */
/*   Updated: 2017/04/09 14:07:44 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GOL_H
# define GOL_H

# include "libft/libft.h"
# include "X11/mlx.h"

# include <stdio.h>
# define DEBUG printf("%d / %s\n", __LINE__, __FILE__)

# define SPACE 32
# define ESC 65307
# define KEY_P 112

# define SCR_W 800
# define SCR_H 600
# define MARGE SCR_W / 10


typedef struct		s_cell
{
	int				n;
	int				n_1;
	int				age;
}					t_cell;

typedef struct		s_env
{
	t_cell			**tab;
	void			*scr;
	void			*win;
	void			*img;
	int				tab_size;
}					t_env;

int					get_static_seed(int i);
int					reset_seed(t_env *env);
int					seed(t_env *env);
int					put_to_img(t_env *env);

#endif
