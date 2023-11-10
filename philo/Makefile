.PHONY: all clean fclean re

CC = clang
NAME = philo
MANDATORY_DIR := .
OBJS_DIR := objects
BONUS_OBJS_DIR := bonus_objects
INC_DIR := includes
CFLAGS = -Wall -Wextra -Werror -g3
LIBS := -lpthread

SRCS = $(addprefix $(MANDATORY_DIR)/, philo.c\
		simulation.c\
		utils.c\
		utils_2.c\
		free_resources.c\
		philo_routine.c\
		actions.c\
		arbiter_routine.c\
		init_table.c\
		init_philos.c\
		init_forks.c\
		validate_args.c\
		ft_atoi.c\
		ft_isdigit.c\
		ft_isxdigit.c\
		ft_strcmp.c\
		ft_strncmp.c\
		write_mesgs.c\
		)

OBJS = $(patsubst $(MANDATORY_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
# All Src subdirectories
SRC_SUBDIR := $(dir $(OBJS))
# Objects Subdirectories
OBJS_SUBDIR := $(subst $(MANDATORY_DIR), $(OBJS_DIR), $(SRC_SUBDIR))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
	@echo ________________________
	@echo Minishell binary created
	@echo ________________________

$(OBJS_DIR)/%.o: $(MANDATORY_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR)/include -I$(INC_DIR) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(BONUS_OBJS_DIR)

fclean: clean
	rm -rf philo

re: fclean all

