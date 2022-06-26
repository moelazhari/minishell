/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:20:49 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/26 16:58:50 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   join_nodes(t_list *list)
{
	t_node	*tmp;
	char	*str;

	tmp = list->head;
	if (list->n <= 1)
		return ;
	while (tmp != list->tail && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp->type == PIPE)
		tmp = tmp->prev;
	while (tmp != list->head)
	{
		str = tmp->prev->val;
		tmp->prev->val = ft_strjoin2(tmp->prev->val , " ", tmp->val);
		free(str);
		tmp = tmp->prev;
		del_node(list, tmp->next);
	}
}

t_node  *remove_red(t_list *list, t_node *tmp)
{
	if (list->n == 0 || list->n == 1)
		return (NULL);
	while (tmp != list->head)
	{
		if (tmp->type == WORD && ft_strchr("<>", tmp->prev->val[0]))
			del_node(list, tmp);
		else if (ft_strchr("<>", tmp->val[0]))
			del_node(list, tmp);
	   tmp = tmp->prev;
	}
	if (ft_strchr("<>", list->head->val[0]))
		del_node(list, tmp);
	return (tmp);
}

static  t_red   *get_red(t_list *list)
{
	t_red   *red;
	t_node  *tmp;

	red = new_red();
	tmp = list->head;
	while (tmp != list->tail && tmp->type != PIPE)
	{
		if (ft_strchr("<>", tmp->val[0]))
		{
			if (tmp->type == REDIN)
				push_back_red(red, REDIN, ft_strdup(tmp->next->val));
			else if (tmp->type == REDOUT)
				push_back_red(red, REDOUT, ft_strdup(tmp->next->val));
			else if (tmp->type == APPEND)
				push_back_red(red, APPEND, ft_strdup(tmp->next->val));
			else if (tmp->type == HEREDOC)
				push_back_red(red, HEREDOC, ft_strdup(tmp->next->val));
		}
		tmp = tmp->next;
	}
	remove_red(list, tmp);
	return (red);
}

t_cmd  *paser(t_list *list, t_cmd *cmd)
{
	t_red   *red;
	char    **args;

	red = get_red(list);
	join_nodes(list);
	if (!list->n)
		args = NULL;
	else
		args = ft_split(list->head->val, ' ');
	push_back_cmd(cmd, args, red);
	if (list->n == 0 || list->n == 1)
	{
		if (list->n == 1)
			clear_list(list);
		return (cmd);
	}
	else
	{
		del_node(list, list->head);
		del_node(list, list->head);
		paser(list, cmd);
	}
	return (cmd);
}