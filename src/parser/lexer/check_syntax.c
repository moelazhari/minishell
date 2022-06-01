/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:39:43 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/01 15:14:01 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_metachar(t_node *tmp)
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

int	check_syntax(t_list *list)
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
