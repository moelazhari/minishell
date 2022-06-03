/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/03 15:50:34 by mazhari          ###   ########.fr       */
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

void print_list(t_list *list)
{
	t_node *tmp;
	int i;

	tmp = list->head;
	i = 0;
	printf("number of nodes %d: \n", list->n);
	while (i < list->n)
	{
		printf("%d node taype: %d val: %s\n", i, tmp->type, tmp->val);
		tmp = tmp->next;
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line; // bufer to store the commandline
	t_list	*list;
	t_cmd	*cmd;
	
	cmd = new_cmd();
	while(1)
	{
		line = prompt();
		list = lexer(line, env);
		print_list(list);
		cmd = paser(list, cmd);
	}	return (0);
}