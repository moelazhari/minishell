/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:14:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/19 19:53:08 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void is_metacharacters(t_list *list,char *line)
// {
// 	if ()
// }


t_list	*tokenizer(char *line)
{
	t_list *list;

	list = new_list();
	while (*line)
	{
		if (*line == ' ')
		{
			while (*line == ' ')
				line++;
			push_back(list, WSPACE, " ");
		}
		// else if (ft_strchr("|<>$", *line));
		//  	is_metacharacters(list, line);
		// if (ft_strchr("'\"", *line))
		// 	is_quote(list, line);
		line++;
	}
	
	return (list);
}