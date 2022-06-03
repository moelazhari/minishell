/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/03 21:21:08 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	get_path(t_cmd *cmd, char **env)
// {
// 	int i;

// 	i = -1;
// 	while (env[++i])
// 		if (!(ft_strncmp("PATH", env[i], 4)))
// 			break ;
// 	cmd->path = ft_split((env[i] + 5), ':');
// }

// void print_red(t_red *red)
// {
// 	t_red_node *tmp;
// 	int i;

// 	tmp = red->head;
// 	i = 0;
// 	while (i < red->n)
// 	{
// 		printf("%d node taype: %d filename: %s\n", i, tmp->type, tmp->filename);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }

// void	print_cmd(t_cmd   *cmd)
// {
// 	t_cmd_node  *tmp;
// 	int i;

// 	i = 0;
//     if (!cmd)
//         return ;
// 	tmp = cmd->head;
//     printf("number of nodes %d: \n", cmd->n);
// 	while (tmp)
// 	{
// 		i = 0;
// 		if (tmp->args)
// 		{
// 	        while (tmp->args[i])
// 	        {
// 			    printf("%s\n", tmp->args[i]);
// 	            i++;
// 	        }
// 		}
// 		print_red(tmp->red);
// 		tmp = tmp->next;
// 	}
// }

// void print_list(t_list *list)
// {
// 	t_node *tmp;
// 	int i;

// 	tmp = list->head;
// 	i = 0;
// 	printf("number of nodes %d: \n", list->n);
// 	while (i < list->n)
// 	{
// 		printf("%d node taype: %d val: %s\n", i, tmp->type, tmp->val);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }

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
	char	*line;
	t_list	*list;
	t_cmd	*cmd;
	
	while(1)
	{
		cmd = new_cmd();
		line = prompt();
		if (line[0] == 0 || is_all_wspace(line))
			continue ;
		if ((list = lexer(line, env)))
		{
			cmd = paser(list, cmd);
			free (cmd);
		}
	}	
	return (0);
}