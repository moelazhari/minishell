/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:14:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/25 20:39:13 by mazhari          ###   ########.fr       */
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

static char	*is_sing(t_list *list, char *line)
{
	line++;
	char *str;
	
	str = NULL;
	if (*line == '?')
	{
		push_back(list, EXIT_STATUS, "$?");
		line++;
	}
	else if (*line == '"' || *line == '\'')
		return (line);
	else
	{	
		push_back(list, SIGN, "$");
		if(*line <= '9' && *line >= '0')
		{
			str = malloc(sizeof(char) * 2);
			str[0] = *line;
			str[1] = '\0';
			push_back(list, WORD, str);
			line++;
		}
		else
			line = is_word(list, line, " \t\n!\"$%'()*+,-./:;<=>?@[\\]^`|~");
	}
	return (line);
}

static char	*is_dquote(t_list *list, char *line)
{
	line = is_word(list, line + 1, "\"$~");
	if (*line == '$')
	{	
		line = is_sing(list, line);
		if (*line != '"')
			line = is_word(list, line, " \t\n!\"$%'()*+,-./:;<=>?@[\\]^`|~");
	}
	else if (*line == '~')
	{
		is_tilde(list, line);
		line++;
	}
	return (line);	
}

static char	*is_quote(t_list *list, char *line, int *status)
{
	if (*line == '"')
	{
		if (ft_strchr(line + 1, '"'))
			line = is_dquote(list, line);
		else
		{
			printf("minishell: unclosed double quotes\n");
			*status = 258;
			clear_list(list);
			return  (NULL);
		}
	}
	else
	{	
		if (ft_strchr(line + 1, '\''))
			line = is_word(list, line + 1, "'");
		else
		{
			printf("minishell: unclosed single quotes\n");
			*status = 258;
			clear_list(list);
			return  (NULL);
		}
	}
	line++;
	return (line);
}

t_list	*tokenizer(char *line, int *status)
{
	t_list	*list;

	list = new_list();
	while (*line)
	{
		if (ft_strchr(" \t\n\v\f\r", *line))
			line = is_wspace(list, line);
		else if (*line == '\'' || *line == '"')
		{
			if (!(line = is_quote(list, line, status)))
					return (NULL);
		}
		else if (*line == '$')
			line = is_sing(list, line);
		else if (ft_strchr("|<>", *line))
		 	line = is_metacharacters(list, line);
		else if (*line == '~')
			line = is_tilde(list, line);
		else
			line = is_word(list, line, " \t\n\v\f\r\"'$|<>");
	}
	return (list);
}