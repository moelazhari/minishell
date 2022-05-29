/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:14:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/25 15:44:31 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_wspace(t_list *list, char *line)
{
	while (*line && ft_strchr(" \t", *line))
		line++;
	push_back(list, WSPACE, " ");
	return (line);
}

char	*is_word(t_list *list, char *line, char *stop)
{
	char	*val;
	int		i;

	i = 0;
	val = NULL;
	while (!(ft_strchr(stop, line[i])))
		i++;
	val = malloc(sizeof(char) * (i + 1));
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

char	*is_sing(t_list *list, char *line)
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
		push_back(list, SIGN, "$");
	return (line);
}

char	*is_quote(t_list *list, char *line)
{
	if (*line == '"')
	{
		if (ft_strchr(line + 1, '"'))
		{
			line = is_word(list, line + 1, "\"$");
			if (*line == '$')
			{	
				line = is_sing(list, line);
				line =  is_word(list, line, " \"");
				*(line - 1) = '"';
				return (line - 1);
			}
		}
		else
			printf("minishell: unclosed double quotes\n");
	}
	else
	{	
		if (ft_strchr(line + 1, '\''))
			line = is_word(list, line + 1, "'");
		else
			printf("minishell: unclosed singel quotes\n");
	}
	line++;
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

t_list	*tokenizer(char *line)
{
	t_list	*list;

	list = new_list();
	while (*line)
	{
		if (ft_strchr(" \t", *line))
			line = is_wspace(list, line);
		else if (*line == '\'' || *line == '"')
			line = is_quote(list, line);
		else if (*line == '$')
			line = is_sing(list, line);
		else if (ft_strchr("|<>", *line))
		 	line = is_metacharacters(list, line);
		else if (*line == '~')
		{
			push_back(list, SIGN, "$");
			push_back(list, WORD, "HOME");
			line++;
		}
		else
			line = is_word(list, line, " \t\v\f\r\"'$|<>");
	}
	return (list);
}