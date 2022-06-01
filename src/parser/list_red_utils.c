/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_red_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:58:39 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/01 18:07:13 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red_node	*new_red_node(int type, char *filename)
{
	t_red_node *new;

	new = malloc(sizeof(t_node));
	new->type = type;
	new->filename = filename;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_red	*push_back_red(t_red *red, int type, char *filename)
{
	t_red_node	*new;

	new = new_red_node(type, filename);
	new->prev = red->tail;
	if (red->tail)
		red->tail->next = new;
	else
		red->head = new;
	red->tail = new;
	(red->n)++;
	return (red);
}

t_red	*new_red(void)
{
	t_red   *new;

	new = malloc(sizeof(t_red));
    new->n = 0;
	new->head = NULL;
	new->tail = NULL;
	return (new);
}