/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/20 18:33:59 by mazhari          ###   ########.fr       */
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
	(void)env;
	char	*cmd; // bufer to store the commandline
	t_list	*list;
	
	while(1)
	{
		cmd = prompt();
		list = lexer(cmd);
		print_list(list);
	}
	return (0);
}