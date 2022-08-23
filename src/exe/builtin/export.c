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
	i = 0;
	while (g_data.env[i])
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
		i++;
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
		ft_putendl_fd(g_data.env[j], 1);
		i++;
	}
	free(ps);
}

int	existing_var(char *var)
{
	int	i;
	int	j;

	i = 0;
	while (g_data.env[i])
	{
		j = 0;
		while (g_data.env[i][j] == var[j] && var[j] != '=' && var[j])
			j++;
		if ((var[j] == '=' || var[j] == '\0') && g_data.env[i][j] == var[j])
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(char **args)
{
	int		i;

	i = 0;
	if (!args[1])
		sorted_env();
	else if (args[1][0] < 'A' || args[1][0] > 'z' || \
	(args[1][0] > 'Z' && args[1][0] < 'a'))
	{
		ft_putendl_fd("Minishell: export: not a valid identifier", 2);
		g_data.status = 256;
	}
	else if (!existing_var(args[1]) && ft_strrchr(args[1], '='))
	{
		while (g_data.env[i])
			i++;
		g_data.env = realloc_envv(i + 1);
		g_data.env[i] = ft_strdup(args[1]);
		g_data.env[i + 1] = NULL;
	}
}
