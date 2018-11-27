# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 15:47:41 by awoimbee          #+#    #+#              #
#    Updated: 2018/11/27 17:20:47 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CC = gcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIB_X_FD = ./minilibx_macos
	FRAMWRK = -framework OpenGL -framework AppKit
else
	LIB_X_FD = ./minilibx_x11
	FRAMWRK = -lXext -lX11
	#Don't forget you need libxext-dev & libx11-dev
endif

LIB	=	$(LIB_X_FD)/libmlx.a	\
		libft/libft.a					\
		-L$(LIB_X_FD)			\
		-lm -lmlx $(FRAMWRK)

SRC	=	main.c			\
		draw_line.c		\
		useful_funcs.c	\
		read_map.c		\
		render.c

INCS	=	./ $(LIB_X_FD)

CFLAGS	=	-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC) fdf.h
	make -C $(LIB_X_FD) all
	make -C libft/ all
	$(CC) $(CFLAGS) $(addprefix -I,$(INCS)) $(SRC) $(LIB) -o $(NAME)

mlx :
	make -C $(LIB_X_FD) all

libft :
	make -C libft/ all

clean :
	make -C $(LIB_X_FD) clean
	make -C libft/ fclean

fclean : clean
	rm -rf $(NAME)

re : fclean all
