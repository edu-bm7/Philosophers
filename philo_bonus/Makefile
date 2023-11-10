.PHONY: all clean fclean re

CC = clang
NAME = philo_bonus
MANDATORY_DIR := .
OBJS_DIR := objects
BONUS_OBJS_DIR := bonus_objects
INC_DIR := includes
CFLAGS = -Wall -Wextra -Werror -g3
LIBS := -lpthread

SRCS = $(addprefix $(MANDATORY_DIR)/, philo_bonus.c\
		simulation_bonus.c\
		utils_bonus.c\
		utils_2_bonus.c\
		free_resources_bonus.c\
		philo_routine_bonus.c\
		actions_bonus.c\
		arbiter_routine_bonus.c\
		init_table_bonus.c\
		init_philos_bonus.c\
		validate_args_bonus.c\
		write_msgs_bonus.c\
		ft_atoi_bonus.c\
		ft_isdigit_bonus.c\
		ft_isxdigit_bonus.c\
		ft_strcmp_bonus.c\
		ft_strncmp_bonus.c\
		)

OBJS = $(patsubst $(MANDATORY_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
# All Src subdirectories
SRC_SUBDIR := $(dir $(OBJS))
# Objects Subdirectories
OBJS_SUBDIR := $(subst $(MANDATORY_DIR), $(OBJS_DIR), $(SRC_SUBDIR))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIB_DIRS) $(LIBS)
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
	rm -rf philo_bonus

re: fclean all

