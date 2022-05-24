/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:58 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/24 14:53:06 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_Syntax(t_list *list)
{
	t_node tmp;
	int	i;
	int	j;

	tmp = *(list->head);
	i = -1;
	j = 0;
	while (++i < list->n)
	{
		if (tmp.next == NULL)
			if (ft_strchr("|<>", tmp.val[0]))
				printf("minishell: syntax error near unexpected token `newline'\n");	
		if (tmp.type == WORD)
		{
			while (tmp.val[j] != ';')
				j++;
			if (tmp.val[j + 1] == ';')
				printf("minishell: syntax error near unexpected token `;;'\n");
		}		
		tmp = *(tmp.next);
	}
}

t_list *lexer(char *line)
{ 
	t_list	*list;

	list = tokenizer(line);
	check_Syntax(list);
	return (list);
}