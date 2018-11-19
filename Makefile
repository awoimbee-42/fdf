NAME	=	fdf

CC = gcc

LIB	=	-L./minilibx ./minilibx/libmlx.a -lmlx -lXext -lX11

SRC	=	main.c

CFLAGS	=	-Wall#-W

all : $(NAME)

$(NAME) : $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(LIB) $(SRC) -o $(NAME)

$(LIB) :
	make -C minilibx/ all

clean :
	@echo pute

fclean : clean
	rm -rf $(NAME)

re : fclean all