# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 15:47:41 by awoimbee          #+#    #+#              #
#    Updated: 2018/11/20 17:37:42 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CC = gcc

LIB_X_FD = ./libs/minilibx_macos

LIB	=	$(LIB_X_FD)/libmlx.a -L$(LIB_X_FD) -lmlx -framework OpenGL -framework AppKit

LIB	+=	libs/libft/libft.a

SRC	=	src/main.c			\
		src/draw_line.c		\
		src/useful_funcs.c	\
		src/read_map.c

INCS	=	./ ./libs/

CFLAGS	=	-Wall -g -O0

all : $(NAME)

$(NAME) : $(SRC) mlx libft
	$(CC) $(CFLAGS) $(LIB) $(addprefix -I,$(INCS)) $(SRC) -o $(NAME)

mlx :
	make -C $(LIB_X_FD) all

libft :
	make -C libs/libft/ all

clean :
	make -C $(LIB_X_FD) clean
	make -C libs/libft/ clean

fclean : clean
	rm -rf $(NAME)

re : fclean all