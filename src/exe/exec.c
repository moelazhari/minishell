#include "minishell.h"

static int	run_cmd(char *bin_path, t_cmd_node *command)
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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (command->next)
			close(command->next_pipe[0]);
		if (command->prev)
			close(command->prev_pipe[1]);
		execve(bin_path, command->args, g_data.env);
        exit(0);
	}
	free(bin_path);
	return (pid);
}

static int		is_executable(char *bin_path, struct stat f, t_cmd_node *command)
{
	if (f.st_mode & S_IXUSR)
		return (run_cmd(bin_path, command));
	else
	{
		g_data.status = 126;
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(bin_path, 1);
		ft_putendl_fd(": Permission denied", 1);
	}
	free(bin_path);
	return (1);
}

static int		check_bins(t_cmd_node *command)
{
	struct stat		f;
	char			*bin_path;
	char			**path;
	int				i;

	if (ft_strchr(command->args[0], '/'))
		if (lstat(command->args[0], &f) != -1)
			return (is_executable(command->args[0], f, command));
	path = ft_split(get_env_var("PATH"), ':');
	i = 0;
	while (path && path[i])
	{
		bin_path = ft_strjoin2(path[i], "/", command->args[0]);
		if (lstat(bin_path, &f) == -1)
			g_data.status = 127;
		else
		{
			ft_freearr(path);
			return (is_executable(bin_path, f, command));
		}
		free(bin_path);
		i++;
	}
	ft_freearr(path);
	return (0);
}

int	exec_command(t_cmd_node *command)
{
	int	is_builtin;
	int	is_bin;

	if(!command->args || command->args[0] == 0)
		return (0);
	is_builtin = check_builtins(command);
	if (is_builtin != 0)
		return (is_builtin);
	is_bin = check_bins(command);
	if (is_bin != 0)
		return (is_bin);
	g_data.status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (0);
}

void	execute(t_cmd *cmds)
{
    t_cmd_node	*node;
	int			exec;
	int     	tmp_in_out[2];

	signal(SIGINT, SIG_IGN);
	tmp_in_out[0] = dup(STDIN_FILENO);
    tmp_in_out[1] = dup(STDOUT_FILENO);
    node = cmds->head;
    while (node)
    {
		reset_in_out(node);
		exec = exec_command(node);
		if (exec == -1)
			exit_shell(cmds, node->args);
		node = node->next;
	dup2(tmp_in_out[0],STDIN_FILENO);
	dup2(tmp_in_out[1],STDOUT_FILENO);
		 if (exec == -2)
			break ;
	}
	dup2(tmp_in_out[0],STDIN_FILENO);
	dup2(tmp_in_out[1],STDOUT_FILENO);
    while (cmds->n--)
        wait(&g_data.status);
	exit_status();
}