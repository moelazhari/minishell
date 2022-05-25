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
				ft_exit(list, "minishell: syntax error near unexpected token `newline'\n", 2);	
				return (0);
			}
		if (tmp->type == WORD)
		{
			if ((ptr = ft_strchr(tmp->val, ';')))
			{
				if (*(ptr + 1) == ';')
				ft_exit(list, "minishell: syntax error near unexpected token `;;'\n", 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

t_list *lexer(char *line)
{ 
	t_list	*list;

	list = tokenizer(line);
	if (!check_Syntax(list))
		return (NULL);
	return (list);
}