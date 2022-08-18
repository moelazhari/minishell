#include "minishell.h"

void free_exit(t_cmd *cmds, int status)
{
	free_cmd(cmds);
	ft_freearr(g_data.env);
	ft_putstr_fd("exit\n", 1);
	exit(status);
}

int check_arg(char *arg)
{
	int i;

	i = 0;
	while (arg[i] >= '0' && arg[i] <= '9')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

void    exit_shell(t_cmd *cmds, char **args)
{
	if (args[1])
	{
		if (args[2])
        {
			ft_putstr_fd("minishel: exit: too many arguments\n", 2);
            g_data.status = 256;
        }
		else
		{
			if (!check_arg(args[1]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
                free_exit(cmds, 255);
			}
			else
				free_exit(cmds, ft_atoi(args[1]));
		}
	}
    else
	    free_exit(cmds, 0);
}