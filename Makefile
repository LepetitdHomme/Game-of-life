#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: csellier <camillesellier@live.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/04/08 23:29:56 by csellier          #+#    #+#             *#
#*   Updated: 2017/04/09 01:49:16 by csellier         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = game_of_life

SCR = main.c put_to_img.c seed.c

HEADER = gol.h

FLAGS = -Wall -Wextra -Werror

OBJ = $(SCR:.c=.o)

$(NAME) : $(HEADER) $(OBJ)
	make -C libft
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L libft/ -L X11/ -lmlx -lft -lXext -lX11

all : $(NAME)

%.o : %.c $(HEADER)
	gcc $(FLAGS) -I. -c $<

clean :
	make -C libft/ clean
	rm -f $(OBJ)

fclean : clean
	make -C libft/ fclean
	rm -rf $(NAME)

re : fclean all
