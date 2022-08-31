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

static int	print_error(int i)
{
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

static int	syntax_error(t_list *list, t_node *tmp, int i)
{
	t_red_node	*red;
	int			fd;
	t_node		*node;

	node = list->head;
	while (node != tmp)
	{
		if (node->type == HEREDOC)
		{
			signal(SIGINT, SIG_IGN);
			if (node->next)
				red = new_red_node(HEREDOC, node->next->val);
			fd = dup(STDIN_FILENO);
			if (heredoc(red, fd) == -1)
				return (0);
			dup2(fd, STDIN_FILENO);
			free(red);
		}
		node = node->next;
	}
	return (print_error(i));
}

int	check_syntax(t_list *list)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == REDIN || tmp->type == REDOUT || tmp->type == PIPE \
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			if (!tmp->next)
				return (syntax_error(list, list->tail, 2));
			else if (tmp->type == PIPE)
			{
				if (!tmp->prev || tmp->next->type == PIPE)
					return (syntax_error(list, tmp, 0));
			}
			else if (tmp->next->type != WORD && tmp->next->type != SIGN \
					&& tmp->next->type != HEREDOC)
				return (syntax_error(list, tmp, 0));
		}
		tmp = tmp->next;
	}
	return (1);
}
