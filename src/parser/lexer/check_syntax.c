/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:39:43 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/10 19:02:19 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_metachar(t_node *tmp, int *status)
{
	if (!tmp->next)
		return (1);
	if (tmp->next->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		*status = 258;
		return (0);
	}
	return (1);
}

int	check_syntax(t_list *list, int *status)
{
	t_node	*tmp;

	tmp = list->head;
	if (ft_strchr("<|>", list->tail->val[0]))
	{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			*status = 258;	
			return (0);
	}
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->val, ';'))
		{
				ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
				*status = 258;
				return (0);
		}
		else if (ft_strchr("<|>", tmp->val[0]))
			if (!is_metachar(tmp, status))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}
