#include "minishell.h"

void	exit_status(int *status)
{
	if (*status == 3)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		*status = 131;
	}
	else if (*status == 2)
	{
		write(2, "\n", 1);
		*status = 130;
	}
	else if (*status == 126 || *status == 127)
		return ;
	else
		*status = WEXITSTATUS(*status);
}

int	redir_in(t_cmd_node *noeud)
{
    t_red_node	*node;
	int			fd_in;

	fd_in = 0;
    node = noeud->red->head;
	while (node)
    {
        if (node->type == REDIN)
        {
			if (fd_in != 0)
				close(fd_in);
            fd_in = open(node->filename, O_RDONLY);
            if (fd_in == -1)
                return -1;
        }
        node = node->next;
    }
	return fd_in;
}

int redir_out(t_cmd_node *noeud)
{
    t_red_node	*node;
	int			fd_out;

	fd_out = 1;
    node = noeud->red->head;
    while (node)
    {
		if (fd_out != 1 && (node->type == REDOUT || node->type == APPEND))
			close(fd_out);
        if (node->type == REDOUT)
		    fd_out = open(node->filename, O_WRONLY | O_CREAT, 0777);
        else if (node->type == APPEND)
            fd_out = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
        node = node->next;
    }
    return fd_out;
}

// void hair_dog(t_cmd_node *command)
// {
// 	char *line;
// 	t_red_node *node;

// 	node = command->red->head;
// 	while (node)
// 	{
// 		if (node->type == HEREDOC)
// 			line = node->filename;
// 		node = node->next; 
// 	}
// 	while ()
// }

void	reset_in_out(t_cmd_node *command)
{
	int	*fd;
	int	*fd_redir;

	fd = malloc(8);
	fd_redir = malloc(8);
	if ((fd_redir[1] = redir_out(command)) != 1)
	{
		dup2(fd_redir[1], STDOUT_FILENO);
		close(fd_redir[1]);
	}
	if ((fd_redir[0] = redir_in(command)) != 0)
	{
		dup2(fd_redir[0], STDIN_FILENO);
		close(fd_redir[0]);
	}
	if (command->next)
	{
		pipe(fd);
		command->next_pipe = fd;
		if (fd_redir[1] == 1)
			dup2(command->next_pipe[1], STDOUT_FILENO);
		close(command->next_pipe[1]);
	}
	if (command->prev)
	{
		command->prev_pipe = command->prev->next_pipe;
		if (fd_redir[0] == 0)
			dup2(command->prev_pipe[0], STDIN_FILENO);
		close(command->prev_pipe[0]);
	}
}

static int		run_cmd(char *bin_path, t_cmd_node *command)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (command->next)
			close(command->next_pipe[0]);
		if (command->prev)
			close(command->prev_pipe[1]);
		execve(bin_path, command->args, g_env);
        exit(0);
	}
	//free(bin_path);
	return (pid);
}

static int		check_builtins(t_cmd_node *command, int *status)
{
	if (ft_strequ(command->args[0], "exit"))
		return (-1);
	else if (ft_strequ(command->args[0], "echo"))
		return (echo(command->args + 1, status));
	else if (ft_strequ(command->args[0], "cd"))
		return (cd(command->args + 1, status));
	else if (ft_strequ(command->args[0], "pwd"))
		return (ft_pwd(status));
	// else if (ft_strequ(command[0], "export"))
	//  	return (export(command + 1, status));
	// else if (ft_strequ(command[0], "unsetenv"))
	// 	return (unset(command + 1), status);
	else if (ft_strequ(command->args[0], "env"))
		return (print_env(status));
	return (0);
}

static int		is_executable(char *bin_path, struct stat f, t_cmd_node *command, int *status)
{
	if (f.st_mode & S_IXUSR)
		return (run_cmd(bin_path, command));
	else
	{
		*status = 126;
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(bin_path, 1);
		ft_putendl_fd(": Permission denied", 1);
	}
	free(bin_path);
	return (1);
}

static int		check_bins(t_cmd_node *command, int *status)
{
	struct stat		f;
	char			*bin_path;
	char			**path;
	int				i;

	if (ft_strchr(command->args[0], '/'))
		if (lstat(command->args[0], &f) != -1)
			return (is_executable(command->args[0], f, command, status));
	path = ft_split(get_env_var("PATH"), ':');
	i = -1;
	while (path && path[++i])
	{
		bin_path = ft_strjoin2(path[i], "/", command->args[0]);
		if (lstat(bin_path, &f) == -1)
		{
			*status = 127;
			free(bin_path);
		}
		else
		{
			ft_freearr(path);
			return (is_executable(bin_path, f, command, status));
		}
	}
	ft_freearr(path);
	return (0);
}

int	exec_command(t_cmd_node *command, int	*status)
{
	int	is_builtin = 0;
	int pid;

	if(!command->args)
		return (0);
	is_builtin = check_builtins(command, status);
	if (is_builtin < 0)
		return (-1);
	if (is_builtin == 1)
		return (0);
	pid = check_bins(command, status);
	if (pid)
		return (pid);
	*status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (pid);
}

void	execute(t_cmd *cmds, int *status)
{
    t_cmd_node	*node;
	int			pid;
	int     tmp_in_out[2];

	tmp_in_out[0] = dup(STDIN_FILENO);
    tmp_in_out[1] = dup(STDOUT_FILENO);
    node = cmds->head;
    while (node)
    {
		reset_in_out(node);
        pid = exec_command(node, status);
		if (pid == -1)
			exit_shell(cmds, node->args, status);
        node = node->next;
		dup2(tmp_in_out[0],STDIN_FILENO);
		dup2(tmp_in_out[1],STDOUT_FILENO);
	}
    while (cmds->n--)
        wait(status);
	exit_status(status);
}