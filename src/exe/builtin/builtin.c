#include "minishell.h"

int	echo(char **args)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!args[0])
	{
		ft_putstr_fd("\n", 1);
		g_data.status = 0;
		return(1);
	}
	while (args[i] && !(ft_strncmp(args[i++] , "-n", 2)))
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
	return (1);
}

int	ft_pwd(void)
{
	char	*pwd;
	char	buff[4096];

	pwd = getcwd(buff, 4096);
	ft_putendl_fd(pwd, 1);
	g_data.status = 0;
	return (1);
}

int	print_env(void)
{
	int i;

	i = 0;
	while(g_data.env[i++])
	{
		if (!g_data.env[i + 1])
			ft_putstr_fd(g_data.env[i], 1);
		else
			ft_putendl_fd(g_data.env[i], 1);
	}
	g_data.status = 0;
	return(1);
}

