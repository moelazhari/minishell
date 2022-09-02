/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:29:40 by mazhari           #+#    #+#             */
/*   Updated: 2022/09/02 12:07:20 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_sign1(t_list *list, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (ft_isalnum(*line) || *line == '_')
	{
		tmp[i] = *line;
		line++;
		i++;
	}
	tmp[i] = '\0';
	push_back(list, SIGN, "$");
	push_back(list, WORD, tmp);
	return (line);
}

char	*is_sign(t_list *list, char *line)
{
	char	tmp[2];

	line++;
	if (*line == 0 || *line == '"' || *line == '\'')
	{
		if (*(line) == 0 || *(line + 1) == 0)
			push_back(list, WORD, ft_strdup("$"));
		return (line);
	}
	else if (*line == '?')
		push_back(list, EXIT_STATUS, "$?");
	else if (!ft_isalpha(*line) && *line != '_')
	{
		if (ft_isdigit(*line))
			push_back(list, SIGN, "$");
		else
			push_back(list, WORD, ft_strdup("$"));
		tmp[0] = line[0];
		tmp[1] = '\0';
		push_back(list, WORD, ft_strdup(tmp));
	}
	else
		return (is_sign1(list, line));
	return (line + 1);
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
