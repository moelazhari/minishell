/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:56:39 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/29 18:55:17 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(char *path)
{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		if (access(path, F_OK) == -1)
			ft_putendl_fd(": no such file or directory", 2);
		else if (access(path, R_OK) == -1)
			ft_putendl_fd(": permission denied", 2);
		else
			ft_putendl_fd(": not a directory", 2);
		g_data.status = 256;
}

void	change_dir(char *path, int print_path)
{
	char	*cwd;
	char	buff[4097];
	int		ch;

	cwd = getcwd(buff, 4096);
	set_env_var("OLDPWD", ft_strdup(cwd));
	ch = chdir(path);
	if (!ch && cwd)
	{
		cwd = getcwd(buff, 4096);
		set_env_var("PWD", ft_strdup(cwd));
		if (print_path)
			ft_putendl_fd(get_env_var("PWD"), 1);
		g_data.status = 0;
	}
	else if (cwd)
		cd_error(path);
	else if (!cwd && path[0] == '.' && path[1] == '\0')
		ft_putendl_fd("getcwd: cannot access parent directories: \
		No such file or directory", 2);
	return ;
}

void	cd(char **args)
{
	char	*home_path;

	home_path = get_env_var("HOME");
	if (!args[0])
		return (change_dir(home_path, 0));
	else
	{
		if (ft_strequ(args[0], "--"))
			return (change_dir(home_path, 0));
		else if (args[0][0] == '-' && !args[0][2])
			return (change_dir(get_env_var("OLDPWD"), 1));
		return (change_dir(args[0], 0));
	}
}
