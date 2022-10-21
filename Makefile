# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 17:47:10 by hkaddour          #+#    #+#              #
#    Updated: 2022/10/21 15:58:44 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
HEADER = include/pipex.h
CFLAGS = -Wall -Wextra -Werror -g
SRCS = src/main.c \
			 src/pipex_utils.c \
			 src/execution.c

SRCS_B = bonus/main_bonus.c \
				 bonus/heredoc.c \
				 bonus/line.c \
				 bonus/pipeline.c \
				 bonus/utils_bonus.c

LIB = libft/libft.a
INF = infile
OFL = ofiles
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

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
	@mkdir $(OFL)
	mv *.o $(OFL)
	$(CC) $(OFL)/* $(LIB) $(CFLAGS) -o $@

%.o: %.c
	@echo "$(BPurple) Compile $(BYellow) $^ $(BGreen)to $@"
	$(CC) $(CFLAGS) -c $^ -I $(HEADER) 

$(LIB):
	@make -C ./libft

bonus: $(LIB) $(OBJS_B)
	@echo "$(BYellow) make file $(BGreen) $(INF)"
	@touch $(INF)
	@mkdir $(OFL)
	mv *.o $(OFL)
	$(CC) $(OFL)/* $(LIB) $(CFLAGS) -o $(NAME)

clean:
	@echo "$(BRed) Clean"
	@rm -rf $(OFL) $(INF)

#in clean delete infile and outfile
fclean:
	@echo "$(BRed) Fclean"
	@rm -rf $(OFL) $(INF) $(NAME) outfile

re: fclean all

.PHONY: all clean fclean re
