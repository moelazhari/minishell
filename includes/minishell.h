/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:34:07 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/15 18:03:42 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

# define WSPACE -1 // 
# define REDIN -2 // <
# define REDOUT -3 // >
# define APPEND -6 // >>
# define HEREDOC -7 // <<
# define SQUOTE -8 // ''
# define DQUOTE -10 // " "
# define ENV_SIGN -11 // $
# define EXIT_STATUS -12 // $?

typedef struct s_cmd
{
	char	*command;
	char	*program;
	char	**path;
}				t_cmd;

typedef struct	s_node
{
	int				type;
	struct s_node	*prev;
	char			*val;
	struct s_node	*next;
}				t_node;

typedef struct	s_list
{
	int		n; // number of node;
	t_node	*head; // the beginning of the list
	t_node	*tail; // the end of the list
}				t_list;	

// fnc of the prompt
char	*prompt(void); // display prompt and get commandline
// fnc of the parser
t_list	*lexer(char *line); // lexical analyser
t_list	*tokenizer(char *line);// converts the line into list of tokens 
// fnc utils in tokenizer
t_node	*new_node(int type, char *val);
t_node	*push_back(t_list *list, int type, char *val);
t_list	*new_list(void);

#endif