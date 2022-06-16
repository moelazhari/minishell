/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/16 01:32:41 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_all_wspace(char *line)
{
	while (*line && ft_strchr(" \t\v\r", *line))
		line++;
	if (*line == 0)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*list;
	t_cmd	*cmd;
	char	*line;
	int		status;

	init_envv(env);
	status = 0;
	while(1)
	{
		line = prompt();
		if (line[0] == 0 || is_all_wspace(line))
		{
			free(line);
			continue ;
		}
		list = lexer(line, &status);
		if (list)
		{
				cmd = new_cmd();
				cmd = paser(list, cmd);
				execute(cmd, &status);
				free_cmd(cmd);
		}
		free(line);
	}
	ft_freearr(g_env);
	return (0);
}