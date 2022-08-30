/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:39:43 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/22 14:21:33 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(t_node *tmp, int i)
{
	t_red_node *red;
	int			fd;

	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			signal(SIGINT, SIG_IGN);
			red = new_red_node(HEREDOC, tmp->next->val);
			fd = dup(STDIN_FILENO);
			heredoc(red);
			dup2(fd, STDIN_FILENO);
			free(red);
		}
		tmp = tmp->prev;
	}
	if (i == 0)
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	if (i == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
	if (i == 2)
		ft_putendl_fd("minishell: syntax error near \
unexpected token `newline'", 2);
	g_data.status = 258;
	return (0);
}

static int	check_metachar(t_node *tmp)
{
	if (!tmp->next)
		return (1);
	else if (tmp->type == PIPE)
	{
		if (!tmp->prev || tmp->next->type == PIPE)
			return (syntax_error(tmp, 0));
	}
	else
	{
		if (tmp->next->type != WORD && tmp->next->type != SIGN \
			&& tmp->next->type != HEREDOC)
			return (syntax_error(tmp, 0));
	}
	return (1);
}

static int	check_word(t_node *tmp)
{
	char	*ptr;

	ptr = ft_strchr(tmp->val, ';');
	if (*(ptr + 1) == ';')
		return (syntax_error(tmp, 1));
	return (1);
}

int	check_syntax(t_list *list)
{
	t_node	*tmp;

	tmp = list->head;
	if (list->tail->type == REDIN || list->tail->type == REDOUT || \
		list->tail->type == PIPE || list->tail->type == APPEND || \
		list->tail->type == HEREDOC)
			return (syntax_error(list->tail, 2));
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->val, ';'))
			if (!check_word(tmp))
				return (0);
		if (tmp->type == REDIN || tmp->type == REDOUT || tmp->type == PIPE \
			|| tmp->type == APPEND || tmp->type == HEREDOC)
			if (!check_metachar(tmp))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}
