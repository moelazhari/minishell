/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_red_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:58:39 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/20 18:14:48 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red_node	*new_red_node(int type, char *filename)
{
	t_red_node	*new;

	new = malloc(sizeof(t_red_node));
	if (!new)
		malloc_error();
	new->type = type;
	new->filename = filename;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	push_back_red(t_red *red, int type, char *filename)
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
}

t_red	*new_red(void)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		malloc_error();
	new->n = 0;
	new->head = NULL;
	new->tail = NULL;
	return (new);
}
