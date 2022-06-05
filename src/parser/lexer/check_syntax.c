/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:39:43 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/05 14:41:02 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_metachar(t_node *tmp)
{
	if (ft_strchr("<|>", tmp->val[0]))
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
	
	tmp = list->head;
	while (tmp != list->tail)
	{
		if (tmp->type == WORD && ft_strchr(tmp->val, ';'))
		{
				ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
				return (0);
		}
		else
			if (!is_metachar(tmp))
				return (0);
		tmp = tmp->next;
	}
	if (list->tail->val[0] == 0)
		return (1);
	if (ft_strchr("<|>", list->tail->val[0]))
	{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);	
			return (0);
	}
	return (1);
}
