#include "minishell.h"

int	echo(char **args, int *status)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!args[0])
	{
		ft_putstr_fd("\n", 1);
		*status = 0;
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
	status = 0;
	return (1);
}

int	ft_pwd(int *status)
{
	char	*pwd;
	char	buff[4096];

	pwd = getcwd(buff, 4096);
	ft_putendl_fd(pwd, 1);
	*status = 0;
	return (1);
}

int	print_env(int *status)
{
	int i;

	i = 0;
	while(g_env[i++])
	{
		if (!g_env[i + 1])
			ft_putstr_fd(g_env[i], 1);
		else
			ft_putendl_fd(g_env[i], 1);
	}
	status = 0;
	return(1);
}

