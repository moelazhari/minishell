/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:28:39 by mazhari           #+#    #+#             */
/*   Updated: 2022/09/01 17:33:24 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*getvar(char *str)
{
	char	*s;
	char	*ret;
	int		i;

	s = ft_strchr(str, '+');
	if (!s)
		return (ft_strdup(str));
	if (s + 1 == ft_strchr(str, '='))
	{
		i = -1;
		ret = malloc(ft_strlen(str) - 1);
		while (str[++i] != '+')
			ret[i] = str[i];
		while (str[++i])
			ret[i - 1] = str[i];
		ret[i - 1] = '\0';
		return (ret);
	}
	return (ft_strdup(str));
}

int	*sort_index(void)
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
