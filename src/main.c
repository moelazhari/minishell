/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/15 18:18:40 by mazhari          ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line; // bufer to store the commandline
	t_list	*list;
	
	while(1)
	{
		line = prompt();
		list = lexer(line);
	}
	return (0);
}