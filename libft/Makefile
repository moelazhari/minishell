# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/13 15:15:37 by mazhari           #+#    #+#              #
#    Updated: 2022/08/23 22:38:01 by mazhari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=	gcc
FLAGS= -Wall -Wextra -Werror 
NAME =	libft.a

LIB  =  ar rc
B_DIR = build
HEDEAR = libft.h

FILES =	ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_memcmp ft_memcpy \
	ft_memmove ft_memchr ft_memset ft_strchr ft_strlcat ft_strlcpy ft_strlen ft_strncmp ft_strnstr \
	ft_strrchr ft_tolower ft_toupper ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim ft_split \
	ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd minishell \

BOUNS =	ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone \
		ft_lstclear ft_lstiter ft_lstmap

OBJS = $(addprefix $(B_DIR)/, $(FILES:=.o))
OBJS_BOUNS = $(BOUNS:=.o)

all: $(NAME)

$(B_DIR)/%.o : %.c $(HEDEAR)
	mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(LIB) $(NAME) $(OBJS)

bouns : all
	$(CC) $(FLAGS) $(BOUNS)
	$(LIB) $(NAME) $(OBJS_BOUNS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BOUNS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

