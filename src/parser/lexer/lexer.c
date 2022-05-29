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
			if (ft_strchr("|<>", tmp->val[0]))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);	
				return (0);
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

t_list	*expaned(t_list *list, char **env)
{
	t_node	*tmp;
	int		i;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == WSPACE)
			del_node(list, tmp);
		if (tmp->type == SIGN)
		{	
			tmp = tmp->next;
			if (tmp->type == WORD)
			{
				i = -1;
				while (env[++i])
				{
					if (!ft_strncmp(tmp->val, env[i], ft_strlen(tmp->val)))
						tmp->val = *(env + i) + ft_strlen(tmp->val) + 1;
				}
			}
		}
		tmp = tmp->next;
	}
	return (list);
}

t_list *lexer(char *line, char **env)
{ 
	t_list	*list;

	list = tokenizer(line);
	if (!check_Syntax(list))
		return (NULL);
	list = expaned(list, env);
	return (list);
}