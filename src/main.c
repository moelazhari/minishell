/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/10 18:38:33 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_red(t_red *red)
{
	t_red_node *tmp;

	tmp = red->head;
	while (tmp)
	{
		free(tmp->filename);
		tmp = tmp->next;
	}
	free(red);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd_node	*tmp;
	int			i;

	tmp = cmd->head;
	while (tmp)
	{
		i = -1; 
		if (tmp->args)
		{
	        while (tmp->args[++i])
	        	free (tmp->args[i]);
			free(tmp->args);
		}
		if (tmp->red)
			free_red(tmp->red);
		tmp = tmp->next;
	}
	free(cmd);
}

int is_all_wspace(char *line)
{
	while (*line && ft_strchr(" \t\v\r", *line))
		line++;
	if (*line == 0)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*list;
	t_cmd	*cmd;
	char	*line;
	int		status;
	
	status = 0;
	while(1)
	{
		cmd = new_cmd();
		line = prompt();
		if (line[0] == 0 || is_all_wspace(line))
			continue ;
		if ((list = lexer(line, env, &status)))
		{
			execute(paser(list, cmd), &status);
			free_cmd(cmd);
		}
	}	
	return (0);
}