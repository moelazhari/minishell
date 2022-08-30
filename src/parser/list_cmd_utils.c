/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:38:53 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/20 18:05:59 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_char(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
	return (str);
}

static t_cmd_node	*new_cmd_node(char **args, t_red *red)
{
	t_cmd_node	*new;

	new = malloc(sizeof(t_cmd_node));
	if (!new)
		malloc_error();
	new->args = args;
	new->red = red;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	push_back_cmd(t_cmd *cmd, char **args, t_red *red)
{
	t_cmd_node	*new;

	new = new_cmd_node(args, red);
	new->prev = cmd->tail;
	if (cmd->tail)
		cmd->tail->next = new;
	else
		cmd->head = new;
	cmd->tail = new;
	(cmd->n)++;
}

t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		malloc_error();
	new->n = 0;
	new->head = NULL;
	new->tail = NULL;
	return (new);
}
