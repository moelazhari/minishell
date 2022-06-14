/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/14 14:51:01 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freearr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	init_envv(char **env)
{
	int		i;
	
	i = 0;
	while (env[i])
		i++;
	g_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		if (!(g_env[i] = ft_strdup(env[i])))
			{
				ft_freearr(g_env);
				ft_putstr_fd("malloc error\n", 2);
				exit(0);
			}
	g_env[i] = NULL; 
}

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
			ft_freearr(tmp->args);
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

	init_envv(env);
	status = 0;
	while(1)
	{
		line = prompt();
		if (line[0] == 0 || is_all_wspace(line))
		{
			free(line);
			continue ;
		}
		list = lexer(line, &status);
		if (list)
		{
				cmd = new_cmd();
				cmd = paser(list, cmd);
				execute(cmd, &status);
				free_cmd(cmd);
		}
		free(line);
	}	
	return (0);
}