# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 17:47:10 by hkaddour          #+#    #+#              #
#    Updated: 2022/10/18 18:31:35 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
HEADER = ft_pipex.h
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.c \
			 src/pipex_utils.c \
			 src/execution.c

LIB = libft/libft.a
INF = infile
OFL = ofiles
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


$(NAME): $(LIB) $(OBJS)
	@echo "$(BYellow) make file $(BGreen) $(INF)"
	@touch $(INF)
	@echo "$(BYellow) Make $(BGreen) $@"
	@mv $(OBJS) $(OFL)
	@$(CC) $(OFL)/* -o $@

%.o: %.c
	@echo "$(BPurple) Compile $(BYellow) $^ $(BGreen)to $@"
	@$(CC) $(CFLAGS) -c $^ -I $(HEADER) 

$(LIB):
	@mkdir $(OFL)
	@make -C ./libft

clean:
	@echo "$(BRed) Clean"
	@rm -rf $(OFL) $(INF)

fclean: clean
	@echo "$(BRed) Fclean"
	@rm -rf $(OFL) $(INF) $(NAME)

re: fclean all

.PHONY: all clean fclean re
