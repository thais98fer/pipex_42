# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thfernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/16 14:35:27 by thfernan          #+#    #+#              #
#    Updated: 2025/12/16 20:34:25 by thfernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Wextra -Werror -g3 -I libft
CC = CC

LIBFT_A = libft/libft.a
LIBFT_DIR = libft

SRCS = pipex.c

OBJS = $(SRCS:.c=.o)

#==================================================#
#                      rules                       #
#==================================================#

# Colors
RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "$(BLUE)Creating $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_A) -o $(NAME)

$(LIBFT_A):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) all

%.o: %.c
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@rm -f $(OBJS)
	@rm -f *.o
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
