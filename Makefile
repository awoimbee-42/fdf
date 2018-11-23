# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 15:47:41 by awoimbee          #+#    #+#              #
#    Updated: 2018/11/23 18:54:57 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CC = gcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIB_X_FD = ./libs/minilibx_macos
	FRAMWRK = -framework OpenGL -framework AppKit
else
	LIB_X_FD = ./libs/minilibx_x11
	FRAMWRK = -lXext -lX11
	#"Don't forget you need libxext-dev & libx11-dev"
endif

LIB	=	$(LIB_X_FD)/libmlx.a	\
		libs/libft/libft.a		\
		-L$(LIB_X_FD)			\
		-lm -lmlx $(FRAMWRK)

SRC	=	src/main.c			\
		src/draw_line.c		\
		src/useful_funcs.c	\
		src/read_map.c		\
		src/render.c

INCS	=	./ ./libs/ $(LIB_X_FD)

CFLAGS	=	-Wall -g -O0

all : $(NAME)

$(NAME) : $(SRC) mlx libft
	$(CC) $(CFLAGS) $(addprefix -I,$(INCS)) $(SRC) $(LIB) -o $(NAME)

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