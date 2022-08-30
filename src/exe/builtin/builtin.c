/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:57:11 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/30 12:43:43 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_newline(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 2;
		if (ft_strncmp(args[i], "-n", 2))
			return (i);
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
			return (i);
		i++;
	}
	return (i);
}

void	echo(char **args)
{
	int	i;
	int	n;

	i = no_newline(args);
	n = i;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	g_data.status = 0;
}

void	print_env(int n)
{
	char	*pwd;
	char	buff[4096];
	int		i;

	i = 0;
	if (n == 1)
	{
		pwd = getcwd(buff, 4096);
		ft_putendl_fd(pwd, 1);
		g_data.status = 0;
		return ;
	}	
	while (g_data.env[i] && ft_strrchr(g_data.env[i], '='))
	{
		ft_putendl_fd(g_data.env[i], 1);
		i++;
	}
	g_data.status = 0;
}

void	unset(char **args)
{
	int		i;
	int		j;
	char	*var;

	i = -1;
	var = args[0];
	if (!var)
		return ;
	while (g_data.env[++i])
	{
		j = 0;
		while (g_data.env[i][j] == var[j] && var[j] != '=' && var[j])
			j++;
		if ((g_data.env[i][j] == '=' || !g_data.env[i][j]) && var[j] == '\0')
		{
			free(g_data.env[i]);
			while (g_data.env[i])
			{
				g_data.env[i] = g_data.env[i + 1];
				i++;
			}
			break ;
		}
	}
	unset(args + 1);
}

int	builtins(t_cmd_node *command)
{
	int		i;
	char	*tmp;

	i = -11;
	tmp = ft_strlower(command->args[0]);
	if (ft_strequ(command->args[0], "exit"))
		i = -1;
	if (ft_strequ(tmp, "echo"))
		echo(command->args + 1);
	else if (ft_strequ(command->args[0], "cd"))
		cd(command->args + 1);
	else if (ft_strequ(tmp, "pwd"))
		print_env(1);
	else if (ft_strequ(command->args[0], "export"))
		ft_export(command->args);
	else if (ft_strequ(command->args[0], "unset"))
		unset(command->args + 1);
	else if (ft_strequ(tmp, "env"))
		print_env(0);
	else
		i = 0;
	free(tmp);
	return (i);
}
