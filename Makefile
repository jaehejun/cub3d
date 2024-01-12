# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 19:32:59 by jaehejun          #+#    #+#              #
#    Updated: 2024/01/12 22:47:15 by jaehejun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

CC		=	CC

CFLAGS	=	-Wall -Wextra -Werror -I./libft #-fsanitize=address -g

SRCS	=	main.c\
			src/utils.c\
			src/check_argument.c\
			src/load_scene.c\
			src/load_texture.c\
			src/set_texture_and_rgb.c\
			src/load_map.c\
			src/set_map_array.c\
			src/is_closed_map.c\
			src/check_map_from_outside.c\
			
			

OBJS	=	$(SRCS:.c=.o)

LIBFT	=	./libft/libft.a

all		:	$(LIBFT) $(NAME)

$(LIBFT):
	make -C ./libft

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re:
	make fclean
	make all

.PHONY = all clean fclean re
