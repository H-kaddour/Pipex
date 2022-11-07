# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 17:47:10 by hkaddour          #+#    #+#              #
#    Updated: 2022/11/07 14:51:25 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
HEADER = include/pipex.h
CFLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix mandatory/, main.c execution_utils.c execution.c)
SRCS_B = $(addprefix bonus/, main_bonus.c heredoc.c gnl.c pipeline.c \
				 utils_bonus.c ../mandatory/execution_utils.c)

LIB = libft/libft.a
INF = infile
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;38;5;205m
BRed=\033[1;31m
 
all : tag $(INF) $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo "\n$(BBlue)Compline object files to $(BPurple)$(NAME)"
	@$(CC) $(OBJS) $(LIB) -o $@

%.o: %.c $(HEADER)
	@/bin/echo -n "."
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

bonus: $(INF) $(LIB) $(OBJS_B)
	@/bin/echo -n "."
	@$(CC) $(OBJS_B) $(LIB) -o $(NAME)

$(LIB):
	@make -C ./libft

$(INF):
	@touch $@

tag:
	@echo "$(BGreen)"
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗ BY HKADDOUR"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"


clean:
	@echo "$(BRed)clean"
	@make clean -C ./libft
	@rm -rf $(OBJS) $(OBJS_B)

fclean:
	@echo "$(BRed)fclean"
	@make fclean -C ./libft
	@rm -rf $(NAME) $(OBJS) $(OBJS_B)

re: fclean all

.PHONY: all bonus tag clean fclean re
