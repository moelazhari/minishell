/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:01:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/24 17:36:09 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freearr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

static void	free_red(t_red *red)
{
	t_red_node	*tmp;
	t_red_node	*forfree;

	tmp = red->head;
	while (tmp)
	{
		forfree = tmp;
		free(tmp->filename);
		tmp = tmp->next;
		free(forfree);
	}
	free(red);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd_node	*tmp;
	t_cmd_node	*forfree;

	tmp = cmd->head;
	while (tmp)
	{
		forfree = tmp;
		if (tmp->args)
			ft_freearr(tmp->args);
		if (tmp->red)
			free_red(tmp->red);
		tmp = tmp->next;
		free(forfree);
	}
	free(cmd);
}

void	malloc_error(void)
{
	ft_putendl_fd("malloc error", 2);
	exit(1);
}
