/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:29:40 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/30 14:11:26 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_sing1(t_list *list, char *line)
{
	char	*str;

	push_back(list, SIGN, "$");
	if (*line <= '9' && *line >= '0')
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			malloc_error();
		str[0] = *line;
		str[1] = '\0';
		push_back(list, WORD, str);
		line++;
	}
	else
		line = is_word(list, line, " \t\n!\"%'()*+,-./:;<=>?@[\\]^`|~$");
	return (line);
}

char	*is_sing(t_list *list, char *line)
{
	line++;
	if (*line == 0)
		push_back(list, WORD, ft_strdup("$"));
	else if (*line == '?')
	{
		push_back(list, EXIT_STATUS, "$?");
		line++;
	}
	else if (ft_strchr(" \t\n!\"%'()*+,-./:;<=>?@[\\]^`|~$", *line))
	{
		if (*line == '"' || *line == '\'')
		{	
			push_back(list, WORD, ft_strdup("$"));
			return (line);
		}
		line++;
	}
	else
		line = is_sing1(list, line);
	return (line);
}

char	*is_word(t_list *list, char *line, char *stop)
{
	char	*val;
	int		i;

	i = 0;
	while (!(ft_strchr(stop, line[i])))
		i++;
	val = malloc(sizeof(char) * (i + 1));
	if (!val)
		malloc_error();
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

static char	*is_herdoc(t_list *list, char *line)
{
	push_back(list, HEREDOC, "<<");
	line = line + 2;
	if (*line && *line != '<' && *line != '>' \
		&& *line != '|')
	{
		while (*line && ft_strchr(" \t\n\v\f\r", *line))
				line++;
		if (*line)
			line = is_word(list, line, " \t\n\v\f\r|<>");
	}
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
			return (is_herdoc(list, line));
		else
			push_back(list, REDIN, "<");
	}
	else if (*line == '|')
		push_back(list, PIPE, "|");
	line++;
	return (line);
}
