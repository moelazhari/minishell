#include "minishell.h"

void	proc_signal_handler(int sig)
{
	if (sig == SIGINT)
		write(1,"\n",1);
}

static int		run_cmd(char *bin_path, char **args, int fd_out, int *status)
{
	pid_t	pid;

	pid = fork();

	if (signal(SIGINT, proc_signal_handler))
		*status = 130;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
        dup2(fd_out, 1);
		execve(bin_path, args, g_env);
        exit(0);
	}
	free(bin_path);
	return (pid);
}

static int		check_builtins(char **command, int fd_out)
{
    (void)fd_out;
	if (ft_strequ(command[0], "exit"))
		return (-1);
	// else if (ft_strequ(command[0], "echo"))
	// 	return (echo_builtin(command + 1, fd_out));
	else if (ft_strequ(command[0], "cd"))
		return (cd_builtin(command + 1, fd_out));
	// else if (ft_strequ(command[0], "setenv"))
	// 	return (setenv_builtin(command + 1));
	// else if (ft_strequ(command[0], "unsetenv"))
	// 	return (unsetenv_builtin(command + 1));
	// else if (ft_strequ(command[0], "env"))
	// {
	// 	print_env();
	// 	return (1);
	// }
	 return (0);
}

static int		is_executable(char *bin_path, struct stat f, char **command, int fd_out, int *status)
{
	if (f.st_mode & S_IXUSR)
		return (run_cmd(bin_path, command, fd_out, status));
	else
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(bin_path, 1);
		ft_putendl_fd(": Permission denied", 1);
	}
	free(bin_path);
	return (1);
}
// char	*ft_strjoin2(char *s1, char *s2, char *s3)
// {
// 	char *tmp;
// 	char *ret;

// 	tmp = ft_strjoin(s1, s2);
// 	ret = ft_strjoin(tmp, s3);
// 	free(tmp);
// 	return (ret);
// }
static int		check_bins(char **command, int fd_out, int *status)
{
	struct stat		f;
	char			*bin_path;
	char			**path;
	int				i;

	if (ft_strchr(command[0], '/'))
		if (lstat(command[0], &f) != -1)
			return (is_executable(command[0], f, command, fd_out, status));
	path = ft_split(get_env_var("PATH"), ':');
	i = -1;
	while (path && path[++i])
	{
		bin_path = ft_strjoin2(path[i], "/", command[0]);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
		{
			ft_freearr(path);
			return (is_executable(bin_path, f, command, fd_out, status));
		}
	}
	ft_freearr(path);
	return (0);
}


int	redir_in(t_cmd_node *noeud, int fd0)
{
    t_red_node	*node;
	int			fd_in;

    node = noeud->red->head;
	if (noeud->prev)
		fd_in = fd0;
	else
		fd_in = 0;
	while (node)
    {
        if (node->type == REDIN)
        {
            fd_in = open(node->filename, O_RDONLY);
            if (fd_in == -1)
                return -1;
        }
        node = node->next;
    }
    dup2(fd_in, 0);
	return fd_in;
}

int redir_out(t_cmd_node *noeud, int fd1)
{
    t_red_node	*node;
	int			fd_out;

	fd_out = 1;
    node = noeud->red->head;
    while (node)
    {
        if (node->type == REDOUT)
            fd_out = open(node->filename, O_WRONLY | O_CREAT, 0777);
        else if (node->type == APPEND)
            fd_out = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
        node = node->next;
    }
	if (fd_out == 1 && noeud->next)
		fd_out = fd1;
    return fd_out;
}

int	exec_command(t_cmd_node *command, int *fd, int *status)
{
	//struct stat	f;
	int	is_builtin;
	int pid;
	int	fd_out;

	redir_in(command, fd[0]);
	fd_out = redir_out(command, fd[1]);
	if ((is_builtin = check_builtins(command->args, fd_out)) == 1)
		return (0);
	if ((pid = check_bins(command->args, fd_out, status)))
		return (pid);
	if (is_builtin < 0)
		return (-1);
	ft_putendl_fd("minishell: command not found: ", 1);
	ft_putendl_fd(command->args[0], 1);
	return (pid);
}

void execute(t_cmd *cmds, int *status)
{
    t_cmd_node *node;
    int     fd[2];
    int     tmp_in_out[2];
	int 	pid;

    node = cmds->head;
    tmp_in_out[0] = dup(0);
    tmp_in_out[1] = dup(1);
    pipe(fd);
    while (node)
    {
        pid = exec_command(node, fd, status);
        close(fd[1]);
        node = node->next;
    }
	//waitpid(pid, status, 0);
    while (cmds->n--)
        wait(0);
    dup2(tmp_in_out[0],0);
    dup2(tmp_in_out[1],1);
} 