# Makefile

NAME = ex1

SRCS = main.c 

all :  $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME) `sdl2-config --cflags --libs`

fclean:
	rm -f $(NAME)

re: fclean all