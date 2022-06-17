/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:29:40 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/17 16:26:36 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_word(t_list *list, char *line, char *stop)
{
	char	*val;
	int		i;

	i = 0;
	while (!(ft_strchr(stop, line[i])))
		i++;
	val = malloc(sizeof(char) * (i));
	i = 0;
	while (!(ft_strchr(stop, *line)))
	{
		val[i++] = *line;
		line++;
	}
	val[i] = '\0';
	push_back(list, WORD, val);
	return (line);
}

char	*is_metacharacters(t_list *list, char *line)
{
	if (*line == '>')
	{
		if (*(line + 1) == '>')
		{
			push_back(list, APPEND, ">>");
			line++;
		}
		else
			push_back(list, REDOUT, ">");
	}
	else if (*line == '<')
	{
		if (*(line + 1) == '<')
		{
			push_back(list, HEREDOC, "<<");
			line++;
		}
		else
			push_back(list, REDIN, "<");
	}
	else if (*line == '|')
		push_back(list, PIPE, "|");
	line++;
	return (line);
}

char	*is_tilde(t_list *list,char *line)
{
	push_back(list, SIGN, "$");
	push_back(list, WORD, ft_strdup("HOME"));
	line++;
	return (line);
}