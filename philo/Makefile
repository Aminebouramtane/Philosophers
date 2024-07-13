NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRC = main.c utils.c philo.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all