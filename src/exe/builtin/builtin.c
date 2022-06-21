#include "minishell.h"

int	echo(char **args, int fd_out, int *status)
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
		ft_putstr_fd(args[i++], fd_out);
		if (args[i]) 
			ft_putstr_fd(" ", fd_out);
	}
	if (!n)
		ft_putstr_fd("\n", fd_out);	
	status = 0;
	return (1);
}

int	ft_pwd(int *status)
{
	char	*pwd;
	char	buff[4097];

	pwd = getcwd(buff, 4096);
	ft_putstr_fd(pwd, 1);
	status = 0;
	return (0);
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

void    exit_shell(t_cmd *cmds)
{
	free_cmd(cmds);
	ft_freearr(g_env);
	exit(0);
}

