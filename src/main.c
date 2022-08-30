/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/29 19:20:02 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(int exit_stat)
{
	if (exit_stat == 3)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_data.status = 131;
	}
	else if (exit_stat == 2)
	{
		write(2, "\n", 1);
		g_data.status = 130;
	}
	else if (g_data.status == 126 || g_data.status == 127)
		return ;
	else
		g_data.status = WEXITSTATUS(exit_stat);
}

int	main(int ac, char **av, char **env)
{
	t_list	*list;
	t_cmd	*cmd;
	char	*line;

	g_data.env = NULL;
	init_envv(env, ac, av);
	while (1)
	{
		line = prompt();
		if (!line)
			continue ;
		list = lexer(line);
		if (list)
		{
			cmd = paser(list, new_cmd());
			clear_list(list);
			execute(cmd);
			free_cmd(cmd);
		}
		free(line);
	}
	ft_freearr(g_data.env);
	return (0);
}
