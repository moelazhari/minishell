/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:58 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/25 15:26:17 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(t_node *tmp)
{
	if (tmp->type == PIPE || tmp->type == REDIN || tmp->type == REDOUT\
		|| tmp->type == HEREDOC || tmp->type == APPEND)
		if (tmp->next->type != WORD && tmp->next->type != WSPACE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			return (0);
		}
	return (1);
}

int	check_Syntax(t_list *list)
{
	t_node	*tmp;
	char	*ptr;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			if (tmp->type == PIPE || tmp->type == REDIN || tmp->type == REDOUT\
				|| tmp->type == HEREDOC || tmp->type == APPEND)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);	
				return (0);
			}
		}
		if (tmp->type == WORD)
		{
			if ((ptr = ft_strchr(tmp->val, ';')))
			{
				if (*(ptr + 1) == ';')
				ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
				return (0);
			}
		}
		else
			if (!is_metachar(tmp))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	expaned_sign(t_list *list, t_node *tmp, char **env)
{
	int	i;

	i = -1;
	tmp = tmp->next;
	if (tmp->val[0] == 0)
	{
		tmp->prev->type = WORD;
		del_node(list, tmp);
	}
	else 
	{
		while (env[++i])
		{
			if (!ft_strncmp(tmp->val, env[i], ft_strlen(tmp->val)))
			{
				tmp->val = *(env + i) + ft_strlen(tmp->val) + 1;
				break ;
			}
		}
		if (!env[i])
			del_node(list, tmp);
		del_node(list, tmp->prev);
	}
}

void	combaine_words(t_list *list)
{
	t_node *tmp;
	int i;
    
	i = -1;
	tmp = list->tail;
	while (++i < list->n)
	{
		if (tmp->type == WORD && tmp->prev->type == WORD)
		{
			tmp->prev->val = ft_strjoin(tmp->prev->val, tmp->val);
				tmp = tmp->prev;	
				del_node(list, tmp->next);
		}
		else
			tmp = tmp->prev;
	}
}

t_list	*expaned(t_list *list, char **env)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == SIGN)
		{
			expaned_sign(list, tmp, env);
		}
		tmp = tmp->next;
	}
	combaine_words(list);
	return (list);
}

t_list	*lexer(char *line, char **env)
{ 
	(void)env;
	t_list	*list;

	list = tokenizer(line);
	if (!check_Syntax(list))
		return (NULL);
	list = expaned(list, env);
	return (list);
}