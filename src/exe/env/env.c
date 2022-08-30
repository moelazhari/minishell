/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:56:55 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/29 18:53:20 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_data.env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_startcmp(g_data.env[i], tmp))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
	}
	return (i);
}

char	**realloc_envv(int new_size)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(1);
	}
	i = 0;
	while (g_data.env && g_data.env[i] && i < new_size)
	{
		new[i] = ft_strdup(g_data.env[i]);
		free(g_data.env[i]);
		i++;
	}
	free(g_data.env);
	return (new);
}

char	*get_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_data.env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_startcmp(g_data.env[i], tmp))
		{
			free(tmp);
			return (ft_strchr(g_data.env[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

void	set_env_var(char *key, char *value)
{
	int		pos;
	char	*tmp;

	pos = find_env_var(key);
	if (g_data.env[pos] && value)
	{
		tmp = ft_strjoin("=", value);
		free(g_data.env[pos]);
		if (value)
			g_data.env[pos] = ft_strjoin(key, tmp);
		else
			g_data.env[pos] = ft_strjoin(key, "=");
		free(value);
		free(tmp);
	}
}

void	init_envv(char **env, int ac, char **av)
{
	int		i;
	char	buff[4096];

	i = 0;
	(void)ac;
	(void)av;
	while (env[i])
		i++;
	g_data.env = malloc(sizeof(char *) * (i + 1 + 3 * (i == 0)));
	if(!g_data.env)
		malloc_error();
	if (i == 0)
	{
		g_data.env[i++] = ft_strjoin("PWD=", getcwd(buff, 4096));
		g_data.env[i++] = ft_strdup("SHLVL=1");
		g_data.env[i++] = ft_strdup("_=/usr/bin/env");
		g_data.env[i] = NULL;
		return ;
	}
	i = -1;
	while (env[++i])
		g_data.env[i] = ft_strdup(env[i]);
	g_data.env[i] = NULL;
	i = ft_atoi(g_data.env[find_env_var("SHLVL")] + 6) + 1;
	set_env_var("SHLVL", ft_itoa(i * (i > 0)));
}
