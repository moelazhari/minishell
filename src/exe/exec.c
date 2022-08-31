/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:36:32 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/30 13:54:32 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_cmd_node *command, int n)
{
	int	is_builtin;
	int	is_bin;

	if (!command->args)
		return (0);
	if (command->args[0][0] != '\0')
	{
		is_builtin = check_builtin(command, n);
		if (is_builtin != 0)
			return (is_builtin);
		is_bin = check_bins(command);
		if (is_bin != 0)
			return (is_bin);
	}
	g_data.status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (0);
}

int	exec_loop(t_cmd *cmds, int *tmp_in_out)
{
	t_cmd_node	*node;
	int			exec;

	node = cmds->head;
	exec = 0;
	while (node)
	{
		if (heredoc(node->red->head, tmp_in_out[0]) == -1)
			break ;
		if (reset_in_out(node))
		{
			exec = exec_command(node, cmds->n);
			if (exec == -2)
				break ;
			if (exec == -1)
				exit_shell(cmds, node->args);
		}
		dup2(tmp_in_out[0], STDIN_FILENO);
		dup2(tmp_in_out[1], STDOUT_FILENO);
		node = node->next;
	}
	return (exec);
}

void	execute(t_cmd *cmds)
{
	int	tmp_in_out[2];
	int	exec;

	signal(SIGINT, SIG_IGN);
	tmp_in_out[0] = dup(STDIN_FILENO);
	tmp_in_out[1] = dup(STDOUT_FILENO);
	exec = exec_loop(cmds, tmp_in_out);
	if (exec >= 1)
		waitpid(exec, &g_data.status, 0);
	while (cmds->n-- - (exec >= 1))
		wait(0);
}
