NAME	=	fdf

LIB	=	minilibx/libmlx.a

SRC	=	main.c

CFLAGS	=	-W

all : $(NAME)

$(NAME) : $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

$(LIB) :
	make -C minilibx/ all

clean :
	@echo pute

fclean : clean
	rm -rf $(NAME)

re : fclean all