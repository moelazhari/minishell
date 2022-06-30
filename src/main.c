/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/30 20:39:12 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_all_wspace(char *line)
{
	while (*line && ft_strchr(" \t\n\v\f\r", *line))
		line++;
	if (*line == 0)
		return (1);
	return (0);
}

int	is_list(t_list *list)
{
	t_node *tmp;

	if (!list)
		return 0;
	tmp = list->head;
	while (tmp)
	{
		if (tmp->val[0] == 0)
			tmp = tmp->next;
		else
			return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*list;
	t_cmd	*cmd;
	char	*line;

	g_data.status = 0;
	init_envv(env);
	while(1)
	{
		line = prompt();
		if (line[0] == 0 || is_all_wspace(line))
		{
			free(line);
			continue ;
		}
		list = lexer(line);
		if (is_list(list))
		{
				cmd = new_cmd();
				cmd = paser(list, cmd);
				execute(cmd);
				free_cmd(cmd);
		}
		free(line);
	}
	ft_freearr(g_data.env);
	return (0);
}