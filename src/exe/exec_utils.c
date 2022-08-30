/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:34:21 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/30 13:55:00 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child(char *bin_path, t_cmd_node *command, int is_builtin)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (command->next)
		close(command->next_pipe[0]);
	if (command->prev)
		close(command->prev_pipe[1]);
	if (is_builtin)
	{
		builtins(command);
		exit(WEXITSTATUS(g_data.status));
	}
	else
		execve(bin_path, command->args, g_data.env);
	exit(0);
}

static int	run_cmd(char *bin_path, t_cmd_node *command, int is_builtin)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(bin_path);
		ft_putendl_fd("Minishell: fork: Resource temporarily unavailable", 2);
		return (-2);
	}
	else if (pid == 0)
		run_child(bin_path, command, is_builtin);
	// if (!ft_strcmp(bin_path, command->args[0]))
	free(bin_path);
	return (pid);
}

static int	is_executable(char *bin_path, struct stat f, \
t_cmd_node *command, char **path)
{
	if (path)
		ft_freearr(path);
	if (f.st_mode & S_IXUSR && !(f.st_mode & S_IFDIR))
		return (run_cmd(bin_path, command, 0));
	else
	{
		g_data.status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(bin_path, 2);
		if (f.st_mode & S_IFDIR)
			ft_putendl_fd(": is a directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
	}
	free(bin_path);
	return (1);
}

int	check_bins(t_cmd_node *command)
{
	struct stat		f;
	char			*bin_path;
	char			**path;
	int				i;

	path = ft_split(get_env_var("PATH"), ':');
	if (ft_strchr(command->args[0], '/') && lstat(command->args[0], &f) != -1)
		return (is_executable(ft_strdup(command->args[0]), f, command, path));
	i = -1;
	while (path && path[++i])
	{
		bin_path = ft_strjoin2(path[i], "/", command->args[0]);
		if (lstat(bin_path, &f) != -1)
			break ;
		free(bin_path);
	}
	if (path && path[i])
		return (is_executable(bin_path, f, command, path));
	ft_freearr(path);
	return (0);
}

int	check_builtin(t_cmd_node *command, int n)
{
	int		x;
	char	*tmp;

	x = 0;
	tmp = ft_strlower(command->args[0]);
	if (ft_strequ(command->args[0], "exit"))
		x = 1;
	if (ft_strequ(tmp, "echo"))
		x = 1;
	else if (ft_strequ(command->args[0], "cd"))
		x = 1;
	else if (ft_strequ(tmp, "pwd"))
		x = 1;
	else if (ft_strequ(command->args[0], "export"))
		x = 1;
	else if (ft_strequ(command->args[0], "unset"))
		x = 1;
	else if (ft_strequ(tmp, "env"))
		x = 1;
	free(tmp);
	if (x && n > 1)
		return (run_cmd(command->args[0], command, 1));
	return (builtins(command));
}
