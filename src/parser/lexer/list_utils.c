/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:51:26 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/19 19:37:00 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(int type, char *val)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	new->type = type;
	new->val = val;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_node	*push_back(t_list *list, int type, char *val)
{
	t_node	*new;

	new = new_node(type, val);
	new->prev = list->tail;
	if (list->tail)
		list->tail->next = new;
	else
		list->head = new;
	list->tail = new;
	(list->n)++;
	return (new);
}

t_list	*new_list(void)
{
	t_list *list;	

	list = malloc(sizeof(t_list));
	list->n = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}