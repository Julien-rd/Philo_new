NAME = philo

CC = cc
INC_DIR = .
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -MMD -g
OBJ_DIR = obj
VPATH = utils utils/core utils/helpers

SRC = actions.c status_check.c cleanup.c gettime.c helper.c initialise_data.c start_simulation.c \
      pickup_fork.c protected_functions.c routine.c philo.c

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DEP = $(OBJ:.o=.d)

.SILENT:

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ) $(DEP)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
