# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 12:36:51 by mazhari           #+#    #+#              #
#    Updated: 2022/06/10 18:37:21 by mazhari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
CFLAGS = -Wall -Werror -Wextra -g

NAME= minishell

INCLUDES= ./includes
HEDEAR= $(INCLUDES)/minishell.h

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
B_DIR= build

PROMPT= $(addprefix prompt/, prompt)
LEXER= $(addprefix lexer/, lexer tokenizer tokenizer1 list_utils check_syntax)
PARSER= $(addprefix parser/, parser list_red_utils list_cmd_utils $(LEXER))
EXE= $(addprefix EXE/, exec)

FILES= $(addprefix src/, main $(PROMPT) $(PARSER) $(EXE))
OBJS= $(addprefix $(B_DIR)/, $(FILES:=.o))

all: $(NAME)

$(B_DIR)/src/%.o: src/%.c $(LIBFT_LIB) $(HEDEAR)
	mkdir -p $(@D)
	$(CC) -I$(INCLUDES) $(CFLAGS) -I /Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/include -c $< -o $@

$(NAME): $(OBJS) $(HEDEAR)
	$(CC) $(CFLAGS) $(LIBFT_LIB) -L /Users/$(USER)/goinfre/.brew/Cellar/readline/8.1.2/lib -lreadline $(OBJS) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(B_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) clean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean f re 