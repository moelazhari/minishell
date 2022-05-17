/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:21:15 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/15 18:13:07 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

char	*prompt(void)
{
	char	*line;

	signal(SIGINT,	sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!(line = readline("Minishell$ ")))
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (line)
		add_history(line);
	rl_on_new_line();
	return (line);
}