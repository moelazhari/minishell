/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:14:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/19 23:17:26 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_wspace(t_list *list, char *line)
{
	while (*line && ft_strchr(" \t\n\v\f\r", *line))
		line++;
	push_back(list, WSPACE, " ");
	return (line);
}

static char	*is_tilde(t_list *list, char *line)
{
	push_back(list, SIGN, "$");
	push_back(list, WORD, ft_strdup("HOME"));
	line++;
	return (line);
}

static char	*is_dquote(t_list *list, char *line)
{
	if (ft_strchr(line, '"'))
	{
		line = is_word(list, line, "\"$~");
		if (*line == '$')
			line = is_sing(list, line);
		else if (*line == '~')
		{
			is_tilde(list, line);
			line++;
		}
		if (*line != '"')
		{
			*(line - 1) = '"';
			return (line - 1);
		}
		return (line + 1);
	}
	else
	{
		printf("minishell: unclosed double quotes\n");
		g_data.status = 258;
		clear_list(list);
		return (NULL);
	}
}

static char	*is_quote(t_list *list, char *line)
{
	if (*line == '"')
	{
		line = is_dquote(list, line + 1);
		if (!line)
			return (NULL);
	}
	else
	{	
		if (ft_strchr(line + 1, '\''))
		{
			line = is_word(list, line + 1, "'");
			line++;
		}
		else
		{
			printf("minishell: unclosed single quotes\n");
			g_data.status = 258;
			clear_list(list);
			return (NULL);
		}
	}
	return (line);
}

t_list	*tokenizer(char *line)
{
	t_list	*list;

	list = new_list();
	if (!list)
		return (NULL);
	while (*line)
	{
		if (ft_strchr(" \t\n\v\f\r", *line))
			line = is_wspace(list, line);
		else if (*line == '\'' || *line == '"')
			line = is_quote(list, line);
		if (!line)
			return (NULL);
		else if (*line == '$')
			line = is_sing(list, line);
		if (!line)
			return (NULL);
		else if (ft_strchr("|<>", *line))
			line = is_metacharacters(list, line);
		else if (*line == '~')
			line = is_tilde(list, line);
		else
			line = is_word(list, line, " \t\n\v\f\r\"'$|<>");
	}
	return (list);
}
