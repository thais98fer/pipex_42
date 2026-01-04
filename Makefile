# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/16 14:35:27 by thfernan          #+#    #+#              #
#    Updated: 2026/01/04 19:43:38 by thfernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

NAME = pipex
BONUS = pipex_bonus

PP_HDR = pipex.h
BONUS_HDR = bonus/pipex_bonus.h

FLAGS = -Wall -Wextra -Werror -g3 -I libft

LIBFT_A = libft/libft.a
LIBFT_DIR = libft

BONUS_DIR = bonus

#=================================================================#
#                           pipex sources                         #
#=================================================================#

SRCS = pipex.c \
		free.c \
		find.c \
		execute.c \
		setup.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = pipex_bonus.c \
			free_bonus.c \
			find_bonus.c \
			execute_bonus.c \
			setup_bonus.c

BONUS_SRC_PATH = $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))
BONUS_OBJS = $(BONUS_SRC_PATH:.c=.o)

#=================================================================#
#                               rules                             #
#=================================================================#

# Colors
RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m

all: $(NAME)
	@echo "$(GREEN)	-> Pipex ready $(RESET)"

$(OBJS): $(PP_HDR)
$(BONUS_OBJS): $(BONUS_HDR)

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(OBJS) $(LIBFT_A) -o $(NAME)
	
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) all

bonus: $(BONUS)

$(BONUS): $(BONUS_OBJS) $(LIBFT_A)
	@$(CC) $(BONUS_OBJS) $(LIBFT_A) -o $(BONUS)
	@echo "$(GREEN)Bonus ready $(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@rm -f *.o
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME) $(BONUS)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
