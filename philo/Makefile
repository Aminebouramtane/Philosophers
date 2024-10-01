NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3

SRC = main.c parce.c actions.c init.c monitoring.c print.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
