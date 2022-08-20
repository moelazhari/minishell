#include "minishell.h"

void	echo(char **args)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!args[0])
	{
		ft_putstr_fd("\n", 1);
		g_data.status = 0;
		return ;
	}
	while (args[i] && !(ft_strncmp(args[i++], "-n", 2)))
		n++;
	i = n;
	while (args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	g_data.status = 0;
	return ;
}

void	ft_pwd(void)
{
	char	*pwd;
	char	buff[4096];

	pwd = getcwd(buff, 4096);
	ft_putendl_fd(pwd, 1);
	g_data.status = 0;
	return ;
}

void	print_env(void)
{
	int	i;

	i = 0;
	while (g_data.env[i])
	{
		ft_putendl_fd(g_data.env[i], 1);
		i++;
	}
	g_data.status = 0;
	return ;
}

void	unset(char *var)
{
	int	i;
	int	j;

	i = 0;
	if (!var)
		return ;
	while (g_data.env[i])
	{
		j = 0;
		while (g_data.env[i][j] == var[j] && var[j] != '=' && var[j])
			j++;
		if (g_data.env[i][j] == '=' && var[j] == '\0')
		{
			free(g_data.env[i]);
			while (g_data.env[i])
			{
				g_data.env[i] = g_data.env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	return ;
}

int	check_builtins(t_cmd_node *command)
{
	char	*rayan;

	if (ft_strequ(command->args[0], "exit"))
		return (-1);
	rayan = ft_strlower(command->args[0]);
	if (ft_strequ(rayan, "echo"))
		echo(command->args + 1);
	else if (ft_strequ(rayan, "cd"))
		cd(command->args + 1);
	else if (ft_strequ(rayan, "pwd"))
		ft_pwd();
	else if (ft_strequ(rayan, "export"))
		ft_export(command->args);
	else if (ft_strequ(rayan, "unset"))
		unset(command->args[1]);
	else if (ft_strequ(rayan, "env"))
		print_env();
	else
	{
		free(rayan);
		return (0);
	}
	free(rayan);
	return (1);
}
