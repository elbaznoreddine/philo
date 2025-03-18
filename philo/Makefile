CFLAGS = -Wall -Wextra -Werror -pthread

SRC = philo.c \
	  parsing_philos.c \
	  philo_utils.c \
	  philo_simulation.c \
	  philo_routine.c \
	  cleanup.c

OBJ = $(SRC:.c=.o)

NAME = philo

all = $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Done maked"

%.o : %.c philo.h
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Done clean"

fclean: clean
	@rm -f $(NAME)
	@echo "Done fclean"

re: fclean all

.PHONY : clean