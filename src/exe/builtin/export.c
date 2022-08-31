/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:56:45 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/29 17:47:13 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*sort_index(void)
{
	int	i;
	int	j;
	int	pos;
	int	*ptr;

	i = 0;
	while (g_data.env[i])
		i++;
	ptr = malloc(i * sizeof(int));
	if (!ptr)
		malloc_error();
	i = -1;
	while (g_data.env[++i])
	{
		j = 0;
		pos = 0;
		while (g_data.env[j])
		{
			if (ft_asciicmp(g_data.env[i], g_data.env[j]) >= 0 && j != i)
				pos++;
			j++;
		}
		ptr[i] = pos;
	}
	return (ptr);
}

void	sorted_env(void)
{
	int	*ps;
	int	i;
	int	j;

	ps = sort_index();
	i = 0;
	while (g_data.env[i])
	{
		j = 0;
		while (ps[j] != i)
			j++;
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(g_data.env[j], 1);
		i++;
	}
	free(ps);
}

int	existing_var(char *var)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (g_data.env && g_data.env[++i])
	{
		j = 0;
		tmp = g_data.env[i];
		while (g_data.env[i][j] == var[j] && var[j] != '=' \
		&& var[j] != '+' && var[j])
			j++;
		if ((var[j] == '=' || var[j] == '\0') && g_data.env[i][j] == var[j])
			g_data.env[i] = ft_strdup(var);
		else if (var[j] == '+')
			g_data.env[i] = ft_strjoin(g_data.env[i], var + j + 2);
		else
			tmp = NULL;
		free(tmp);
		if (g_data.env[i][j] == var[j] || var[j] == '+')
			return (1);
	}
	return (0);
}

int	check_args(char *args)
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
			g_data.env[i] = ft_strdup(args[j]);
			// ft_strchr(args[j], '+')	

			g_data.env[i + 1] = NULL;
		}
	}
	ft_putendl_fd("Minishell: export: not a valid identifier", 2);
	g_data.status = 256;
}
