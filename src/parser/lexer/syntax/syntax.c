/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:39:43 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/30 20:36:55 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_metachar(t_node *tmp)
{
	if (!tmp->next)
		return (1);
	if (tmp->type == PIPE)
	{
		if (!tmp->prev || tmp->next->type == PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			g_data.status = 258;
			return (0);
		}
	}
	else
	{
		if (tmp->next->type != WORD && tmp->next->type != SIGN)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			g_data.status = 258;
			return (0);
		}
	}
	return (1);
}

int is_all_wspace1(char *line)
{
	while (*line && ft_strchr(" \t\n\v\f\r", *line))
		line++;
	if (*line == 0)
		return (1);
	return (0);
}

int	check_syntax(t_list *list)
{
	t_node	*tmp;
	char	*ptr;

	tmp = list->head;
	if (list->tail->type == REDIN ||list->tail->type == REDOUT || list->tail->type == PIPE\
		 || list->tail->type == APPEND || list->tail->type == HEREDOC)
	{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			g_data.status = 258;	
			return (0);
	}
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->val, ';'))
		{
			ptr = ft_strchr(tmp->val, ';');
			if (*(ptr + 1) == ';')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
				g_data.status = 258;
				return (0);
			}
		}
		if (tmp->type == REDIN ||tmp->type == REDOUT || tmp->type == PIPE\
				|| tmp->type == APPEND || tmp->type == HEREDOC)
				if (!is_metachar(tmp))
					return (0);
		tmp = tmp->next;
	}
	return (1);
}