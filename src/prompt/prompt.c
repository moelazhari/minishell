/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:21:15 by mazhari           #+#    #+#             */
/*   Updated: 2022/09/02 11:24:03 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_wspace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr(" \t\n\v\f\r", line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

static void	sig_int_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_data.status = 1;
}

char	*prompt(void)
{
	char	*line;

	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("Minishell$> ");
	if (!line)
		free_exit(NULL, g_data.status);
	else if (is_all_wspace(line))
	{
		free(line);
		line = NULL;
	}
	else
		add_history(line);
	rl_on_new_line();
	return (line);
}
