/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:34:07 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/05 17:14:58 by mazhari          ###   ########.fr       */
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
#include <fcntl.h>

# define WSPACE -1 // ' '
# define PIPE -2 // |
# define REDIN -3 // <
# define REDOUT -4 // >
# define APPEND -5// >>
# define HEREDOC -6 // <<
# define SQUOTES -7// '
# define DQUOTES -8// "
# define SIGN -9 // $
# define EXIT_STATUS -10 // $?
# define WORD -11 // 	

typedef struct	s_node
{
	int				type;
	char			*val;
	struct s_node	*prev;
	struct s_node	*next;
}				t_node;

typedef struct	s_list
{
	int		n; // number of node;
	t_node	*head; // the beginning of the list
	t_node	*tail; // the end of the list
}				t_list;

typedef struct	s_red_node
{
	int					type;
	char				*filename;
	struct s_red_node	*prev;
	struct s_red_node	*next;
}				t_red_node;

typedef struct	s_red
{
	int			n;
	t_red_node	*head; // the beginning of the list
	t_red_node	*tail; // the end of the list
}				t_red;

typedef struct s_cmd_node
{
	char				**args;
	t_red				*red;
	struct s_cmd_node	*prev;
	struct s_cmd_node	*next;
}				t_cmd_node;

typedef struct	s_cmd
{
	int			n; // number of node;
	t_cmd_node	*head; // the beginning of the list
	t_cmd_node	*tail; // the end of the list
}				t_cmd;

// fnc of the prompt
char	*prompt(void); // display prompt and get commandline
void	sig_int_handler(int sig);
// fnc of the parser
t_cmd  *paser(t_list *list, t_cmd *cmd);
// fnc list cmd red utils
t_cmd		*new_cmd(void);
void		push_back_cmd(t_cmd *cmd, char **args, t_red *red);
t_red		*new_red(void);
t_red_node	*new_red_node(int type, char *filename);
void		push_back_red(t_red *red, int type, char *filename);
// lexical analyser
t_list	*lexer(char *line, char **env); // lexical analyser
//fnc utils in tokenizer
t_list	*tokenizer(char *line);// converts the line into list of tokens 
char	*is_word(t_list *list, char *line, char *stop);
char	*is_metacharacters(t_list *list, char *line);
char	*is_tilde(t_list *list,char *line);
//fnc utils in list
t_node	*new_node(int type, char *val);
void	push_back(t_list *list, int type, char *val);
t_list	*new_list(void);
void	del_node(t_list *list, t_node *node);
//syntax fnc
int	check_syntax(t_list *list);
//exec fnc
void execute(t_cmd *cmds);
//fnc exit

#endif