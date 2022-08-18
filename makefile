# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 12:36:51 by mazhari           #+#    #+#              #
#    Updated: 2022/08/18 19:29:06 by yel-khad         ###   ########.fr        #
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
TOKENIZER= $(addprefix	tokenizer/, tokenizer tokenizer1 list_utils)
SYNTAX= $(addprefix syntax/, syntax)
LEXER= $(addprefix lexer/, lexer $(TOKENIZER) $(SYNTAX))
PARSER= $(addprefix parser/, parser list_red_utils list_cmd_utils $(LEXER))
BUILTIN= $(addprefix builtin/, builtin cd exit export)
ENV= $(addprefix env/, env)
EXE= $(addprefix exe/, $(BUILTIN) $(ENV) exec redir)

FILES= $(addprefix src/, main ft_free $(PROMPT) $(PARSER) $(EXE))
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