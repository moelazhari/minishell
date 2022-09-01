/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:56:45 by yel-khad          #+#    #+#             */
/*   Updated: 2022/09/01 17:31:57 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_args(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (0);
	while (args[i] && args[i] != '=')
	{
		if ((!ft_isalnum(args[i]) && args[i] != '+') || \
		(args[i] == '+' && args[i + 1] != '='))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **args)
{
	int	i;
	int	j;

	j = 0;
	if (!args[1])
		return (sorted_env());
	while (args[++j])
	{
		if (!check_args(args[j]))
			break ;
		else if (!existing_var(args[j]))
		{
			i = 0;
			while (g_data.env && g_data.env[i])
				i++;
			g_data.env = realloc_envv(i + 1);
			g_data.env[i] = getvar(args[j]);
			g_data.env[i + 1] = NULL;
		}
	}
	if (!args[j])
		return ;
	ft_putendl_fd("Minishell: export: not a valid identifier", 2);
	g_data.status = 256;
}
