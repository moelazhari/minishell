/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:20:49 by mazhari           #+#    #+#             */
/*   Updated: 2022/09/02 11:32:53 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**malooc_args(t_list *list, char **args)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = list->head;
	while (tmp != list->tail && tmp->type != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp == list->tail)
		i++;
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		malloc_error();
	args[i] = NULL;
	return (args);
}

static char	**get_args(t_list *list, char **args)
{
	t_node	*tmp;
	int		i;

	i = 0;
	args = malooc_args(list, args);
	tmp = list->head;
	while (tmp != list->tail && tmp->type != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp->type == PIPE)
		tmp = tmp->prev;
	if (tmp == list->tail)
		i++;
	while (--(i) >= 0)
	{
		args[i] = ft_strdup(tmp->val);
		tmp = tmp->prev;
		if (tmp)
			del_node(list, tmp->next);
	}
	del_node(list, list->head);
	return (args);
}

static t_node	*remove_red(t_list *list, t_node *tmp)
{
	while (tmp != list->head)
	{
		if (tmp->type == REDIN || tmp->type == REDOUT
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			del_node(list, tmp->next);
			tmp = tmp->prev;
			del_node(list, tmp->next);
		}
		else
			tmp = tmp->prev;
	}
	if (tmp->type == REDIN || tmp->type == REDOUT
		|| tmp->type == APPEND || tmp->type == HEREDOC)
	{
		del_node(list, tmp->next);
		del_node(list, tmp);
	}
	return (tmp);
}

static t_red	*get_red(t_list *list)
{
	t_red	*red;
	t_node	*tmp;

	red = new_red();
	tmp = list->head;
	while (tmp != list->tail && tmp->type != PIPE)
	{
		if (tmp->type == REDIN)
			push_back_red(red, REDIN, ft_strdup(tmp->next->val));
		else if (tmp->type == REDOUT)
			push_back_red(red, REDOUT, ft_strdup(tmp->next->val));
		else if (tmp->type == APPEND)
			push_back_red(red, APPEND, ft_strdup(tmp->next->val));
		else if (tmp->type == HEREDOC)
			push_back_red(red, HEREDOC, ft_strdup(tmp->next->val));
		tmp = tmp->next;
	}
	remove_red(list, tmp);
	return (red);
}

t_cmd	*paser(t_list *list, t_cmd *cmd)
{
	t_red	*red;
	char	**args;

	args = NULL;
	red = get_red(list);
	if (!list->n || list->head->type == PIPE)
		args = NULL;
	else
		args = get_args(list, args);
	push_back_cmd(cmd, args, red);
	if (list->n)
	{
		del_node(list, list->head);
		paser(list, cmd);
	}
	return (cmd);
}
