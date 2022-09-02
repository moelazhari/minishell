/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/09/02 13:14:41 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(void)
{
	if (g_data.status == 3)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_data.status = 131;
	}
	else if (g_data.status == 2)
	{
		write(2, "\n", 1);
		g_data.status = 130;
	}
	else if (g_data.status == 126 || g_data.status == 127 \
	|| g_data.status == 1)
		return ;
	else
		g_data.status = WEXITSTATUS(g_data.status);
}

int	main(int ac, char **av, char **env)
{
	t_list	*list;
	t_cmd	*cmds;
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
			cmds = paser(list, new_cmd());
			clear_list(list);
			execute(cmds);
			free_cmd(cmds);
		}
		free(line);
	}
	return (0);
}
