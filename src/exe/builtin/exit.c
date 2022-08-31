/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:57:21 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/25 14:57:22 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_cmd *cmds, int status)
{
	if (cmds)
		free_cmd(cmds);
	ft_freearr(g_data.env);
	ft_putstr_fd("exit\n", 1);
	exit(status);
}

int	check_arg(char *args)
{
	int	i;

	i = 0;
	if (args[i] == '-' || args[i] == '+')
		i++;
	while (args[i] >= '0' && args[i] <= '9')
		i++;
	if (args[i] == '\0')
		return (1);
	return (0);
}

void	exit_shell(t_cmd *cmds, char **args)
{
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd("minishel: exit: too many arguments\n", 2);
			g_data.status = 256;
		}
		else
		{
			if (!check_arg(args[1]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				free_exit(cmds, 255);
			}
			else
				free_exit(cmds, ft_atoi(args[1]));
		}
	}
	else
		free_exit(cmds, g_data.status);
}
