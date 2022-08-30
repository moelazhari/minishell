/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:56:29 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/30 14:07:16 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (fd_in);
}

int	redir_out(t_cmd_node *noeud)
{
	t_red_node	*node;
	int			fd_out;

	fd_out = 1;
	node = noeud->red->head;
	while (node && fd_out != -1)
	{
		if (fd_out != 1 && (node->type == REDOUT || node->type == APPEND))
			close(fd_out);
		if (node->type == REDOUT)
			fd_out = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (node->type == APPEND)
			fd_out = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		node = node->next;
	}
	if (fd_out != 1 && fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (fd_out);
}

void	rl_write_fd(char *filename, int *fd)
{
	char		*line;
	char		*rline;

	close(fd[0]);
	line = filename;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	rline = readline("> ");
	while (rline && !ft_strcmp(line, rline))
	{
		ft_putendl_fd(rline, fd[1]);
		free(rline);
		rline = readline("> ");
	}
	free(rline);
	close(fd[1]);
	exit(0);
}

int	heredoc(t_red_node *node)
{
	int			pid;
	int			fd[2];
	int			status;

	while (node && node->type != HEREDOC)
		node = node->next;
	if (node)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			rl_write_fd(node->filename, fd);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			ft_putendl_fd("", 1);
			return (-1);
		}
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (0);
}

int	reset_in_out(t_cmd_node *command)
{
	int	fd_redir[2];

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
		return (1);
	}
	ft_putstr_fd("Minishell: : No such file or directory\n", 2);
	return (0);
}
