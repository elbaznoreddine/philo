CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
SRC = philo_bonus.c \
	  parsing_philo_bonus.c \
	  philo_utils_bonus.c \
	  philo_simulation_bonus.c \
	  philo_routine_bonus.c \
	  cleanup_bonus.c

OBJ = $(SRC:.c=.o)

NAME = philo_bonus

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Done maked"

%.o : %.c philo_bonus.h
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Done clean"

fclean: clean
	@rm -f $(NAME)
	@echo "Done fclean"

re: fclean all

.PHONY : clean