/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:14:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/14 14:20:54 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_wspace(t_list *list, char *line)
{
	while (*line && ft_strchr(" \t", *line))
		line++;
	push_back(list, WSPACE, " ");
	return (line);
}

static char	*is_sing(t_list *list, char *line)
{
	line++;
	if (*line == '?')
	{
		push_back(list, EXIT_STATUS, "$?");
		line++;
	}
	else if (*line == '{' && ft_strchr(line + 1, '}'))
	{
		push_back(list, SIGN, "$");
		line = is_word(list, line + 1, "}");
		line++;
	}
	else
	{
		push_back(list, SIGN, "$");
		line = is_word(list, line, " \t!\"$%'()*+,-./:;<=>?@[\\]^`{|}~");
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
			line =  is_word(list, line, "\"");
	}
	else if (*line == '~')
	{
		push_back(list, SIGN, "$");
		push_back(list, WORD, "HOME");
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
			printf("minishell: unclosed singel quotes\n");
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
		if (ft_strchr(" \t", *line))
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
			line = is_word(list, line, " \t\v\f\r\"'$|<>");
	}
	return (list);
}