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
	free(bin_path);
	return (0);
}

int				exec_command(char **command, int fd_out, int *status)
{
	//struct stat	f;
	int			is_builtin;
	int 		pid;

	if ((is_builtin = check_builtins(command, fd_out)) == 1 || (pid = check_bins(command, fd_out, status)))
		return (0);
	if (is_builtin < 0)
		return (-1);
    //printf("%d\n",is_builtin);
	// if (lstat(command[0], &f) != -1)
	// {
	// 	if (f.st_mode & S_IFDIR)
	// 	{
	// 		change_dir(command[0], 0);
	// 		return (0);
	// 	}
	// 	else if (f.st_mode & S_IXUSR)
	// 		return (run_cmd(ft_strdup(command[0]), command, fd_out));
	// }
	//ft_putendl_fd("minishell: command not found: ");
	//ft_putendl_fd(command[0], 1);
	return (pid);
}
int redir_in(t_red *redir, int fd_in)
{
    t_red_node *node;

    node = redir->head;
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
    return fd_in;
}

int redir_out(t_red *redir, int fd_out)
{
    t_red_node *node;

    node = redir->head;
    while (node)
    {
        if (node->type == REDOUT)
            fd_out = open(node->filename, O_WRONLY | O_CREAT, 0777);
        else if (node->type == APPEND)
            fd_out = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
        node = node->next;
    }
    return fd_out;
}

void execute(t_cmd *cmds, int *status)
{
    t_cmd_node *node;
    int     fd[2];
    int     fd_in_out[2];
    int     tmp_in_out[2];
	int 	pid;

    node = cmds->head;
    tmp_in_out[0] = dup(0);
    tmp_in_out[1] = dup(1);
    fd_in_out[0] = 0;
    pipe(fd);
    while (node)
    {
        fd_in_out[1] = 1;
        fd_in_out[0] = redir_in(node->red, fd_in_out[0]);
        dup2(fd_in_out[0], 0);
        fd_in_out[1] = redir_out(node->red, fd_in_out[1]);
        if (fd_in_out[1] == 1 && node->next)
            fd_in_out[1] = fd[1];
        pid = exec_command(node->args, fd_in_out[1], status);
        node = node->next;
        close(fd[1]);
        dup2(fd[0], fd_in_out[0]);
        //close(fd[0]);
    }
	//waitpid(pid, status, 0);
    while (cmds->n--)
        wait(0);
    dup2(tmp_in_out[0],0);
    dup2(tmp_in_out[1],1);
} 