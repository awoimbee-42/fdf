NAME	=	fdf

CC = gcc

LIB_X_FD = ./minilibx_macos

LIB_X	=	$(LIB_X_FD)/libmlx.a -L$(LIB_X_FD) -framework OpenGL -framework AppKit

LIB_FT += libft/libft.a

SRC	=	main.c

INCS	=	./ ./libft/

CFLAGS	=	-Wall -g -O0

all : $(NAME)

$(NAME) : $(SRC) $(LIB_X) $(LIB_FT)
	$(CC) $(CFLAGS) $(LIB_X) $(LIB_FT) $(addprefix -I,$(INCS)) $(SRC) -o $(NAME)

$(LIB_X) :
	make -C $(LIB_X_FD) all

$(LIB_FT) :
	make -C libft/ all

clean :
	make -C $(LIB_X_FD) clean
	make -C libft/ clean

fclean : clean
	rm -rf $(NAME)

re : fclean all