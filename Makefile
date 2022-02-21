# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 17:47:10 by hkaddour          #+#    #+#              #
#    Updated: 2022/02/21 18:24:29 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
HEADER = ft_pipex.h
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_pipex.c \
	   ft_pipex_utils.c \
	   ft_split.c
OBJS = $(SRCS:.c=.o)

BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;38;5;205m
BRed=\033[1;31m
 
all : $(NAME)
	
	@echo " "
	@echo "$(BGreen)==================================="
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗ BY HKADDOUR"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"

%.o: %.c
	@echo "$(BPurple) Compile $(BYellow) $^ $(BGreen)to $@"
	@$(CC) $(CFLAGS) -c $^ -I $(HEADER) 

$(NAME): $(OBJS)
	@echo "$(BYellow) Make $(BGreen) $@"
	@$(CC) -o $@ $^

clean:
	@echo "$(BBlue) Clean"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(BRed) Fclean"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
