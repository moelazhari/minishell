#include "minishell.h"

int		find_env_var(char *var)
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
	i = -1;
	while (g_data.env[++i] && i < new_size)
	{
		new[i] = ft_strdup(g_data.env[i]);
		free(g_data.env[i]);
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
	tmp = ft_strjoin("=", value);
	if (g_data.env[pos])
	{
		free(g_data.env[pos]);
		if (value)
			g_data.env[pos] = ft_strjoin(key, tmp);
		else
			g_data.env[pos] = ft_strjoin(key, "=");
	}
	else
	{
		g_data.env = realloc_envv(pos + 1);
		if (value)
			g_data.env[pos] = ft_strjoin(key, tmp);
		else
			g_data.env[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
}

void	init_envv(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	g_data.env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		if (!(g_data.env[i] = ft_strdup(env[i])))
			{
				ft_freearr(g_data.env);
				ft_putstr_fd("malloc error\n", 2);
				exit(0);
			}
	g_data.env[i] = NULL; 
}
