/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:14:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/20 18:33:17 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_metacharacters(t_list *list,char *line)
{
	if (*line == '>')
	{
		if (*(line + 1) == '>')
		{
			push_back(list, APPEND, ">>");
			return (line + 2);
		}
		push_back(list, REDOUT, ">");	
	}
	if (*line == '<')
	{
		if (*(line + 1) == '<')
		{
			push_back(list, HEREDOC, "<<");
			return (line + 2);
		}
		push_back(list, REDIN, "<");	
	}
	if (*line == '|')
		push_back(list, PIPE, "|");
	return (line + 1);
}

char	*is_squote(t_list *list, char *line)
{
	char	*val;
	int		i;

	i = 0;
	val = NULL;

	while (line[i] != '\'')
		i++;
	val = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (*line != '\'')
	{
		val[i++] = *line;
		line++;
	}
	val[i] = '\0';
	push_back(list, WORD, val);
	return (line + i - 1);
}

char	*is_dquote(t_list *list, char *line)
{
	char	*val;
	int		i;

	i = 0;
	val = NULL;

	while (line[i] != '\"')
		i++;
	val = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (*line != '\"')
	{
		val[i++] = *line;
		line++;
	}
	val[i] = '\0';
	push_back(list, WORD, val);
	return (line + i - 1);
}

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
		if (ft_strchr("|<>$", *line))
		 	line = is_metacharacters(list, line);
		if (*line == '\'' && ft_strchr(++line, '\''))
			line = is_squote(list, line);
		if (*line == '"' && ft_strchr(++line, '"'))
		 	line = is_dquote(list, line);
		line++;
	}
	return (list);
}