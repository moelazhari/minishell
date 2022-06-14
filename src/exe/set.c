#include "minishell.h"

int		find_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_startcmp(g_env[i], tmp))
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
	while (g_env[++i] && i < new_size)
	{
		new[i] = ft_strdup(g_env[i]);
		free(g_env[i]);
	}
	free(g_env);
	return (new);
}

char	*get_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_startcmp(g_env[i], tmp))
		{
			free(tmp);
			return (ft_strchr(g_env[i], '=') + 1);
		}
		free(tmp);
	}
	free(var);
	return (NULL);
}

void	set_env_var(char *key, char *value)
{
	int		pos;
	char	*tmp;

	pos = find_env_var(key);
	tmp = ft_strjoin("=", value);
	if (g_env[pos])
	{
		free(g_env[pos]);
		if (value)
			g_env[pos] = ft_strjoin(key, tmp);
		else
			g_env[pos] = ft_strjoin(key, "=");
	}
	else
	{
		g_env = realloc_envv(pos + 1);
		if (value)
			g_env[pos] = ft_strjoin(key, tmp);
		else
			g_env[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
}