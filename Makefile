##
## EPITECH PROJECT, 2022
## pano
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/utils.c	\
		src/prog.c

CFLAGS	+= -W -Wall -Wextra -lpthread -g

OBJS	=	$(SRC:.c=.o)

NAME	=	panoramix

all:	$(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re