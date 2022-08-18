#include "minishell.h"

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
                return (-1);
        }
        node = node->next;
    }
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
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
		if (fd_out == -1)
			return (-1);
        node = node->next;
    }
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
    return fd_out;
}

int	rl_write_fd(char *filename)
{
    char		*line;
    char    	*rline;
	int			p;
	
	p = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    line = filename;
    rline = readline("> ");
	while (!ft_strcmp(line, rline))
    {
		ft_putendl_fd(rline, p);
		rline = readline("> ");
	}
	close(p);
	return (p);
}

void    heredoc(t_cmd_node *command)
{
    t_red_node	*node;
	int			pid;
	int			p;

    node = command->red->head;
    while (node && node->type != HEREDOC)
        node = node->next;
    if (node)
    {
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			p = rl_write_fd(node->filename);
			exit(0);
		}
		wait(&pid);
		p = open("/tmp/.heredoc", O_RDONLY , 0777);
		unlink("/tmp/.heredoc");
		dup2(p, STDIN_FILENO);
		close(p);
    }
}

void	reset_in_out(t_cmd_node *command)
{
	int	fd_redir[2];

	heredoc(command);
	fd_redir[0] = redir_in(command);
	fd_redir[1] = redir_out(command);
	if (fd_redir[1] != -1 && fd_redir[0] != -1)
	{
	if (command->next)
	{
		pipe(command->next_pipe);
		if (fd_redir[1] == 1)
			dup2(command->next_pipe[1], STDOUT_FILENO);
		close(command->next_pipe[1]);
	}
	if (command->prev)
	{
		command->prev_pipe[0] = command->prev->next_pipe[0];
		command->prev_pipe[1] = command->prev->next_pipe[1];
		if (fd_redir[0] == 0)
			dup2(command->prev_pipe[0], STDIN_FILENO);
		close(command->prev_pipe[0]);
	}
	}
	else 
	{
		ft_putstr_fd("Minishell: : No such file or directory\n", 2);
		exit_status();
	}
}