/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:39:43 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/17 17:32:39 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_metachar(t_node *tmp, int *status)
{
	if (!tmp->next)
		return (1);
	if ( tmp->type == PIPE)
	{
		if (!tmp->prev)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			*status = 258;
			return (0);
		}
	}
	else
	{
		if (tmp->next->type != WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token", 2);
			*status = 258;
			return (0);
		}
	}
	return (1);
}

int	check_syntax(t_list *list, int *status)
{
	t_node	*tmp;
	char	*ptr;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->val, ';'))
		{
			ptr = ft_strchr(tmp->val, ';');
			if (*(ptr + 1) == ';')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
				*status = 258;
				return (0);
			}
		}
		else if (tmp->type == REDIN ||tmp->type == REDOUT || tmp->type == PIPE)
			if (!is_metachar(tmp, status))
				return (0);
		tmp = tmp->next;
	}
	if (list->tail->type == REDIN ||list->tail->type == REDOUT || list->tail->type == PIPE)
	{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			*status = 258;	
			return (0);
	}
	return (1);
}
