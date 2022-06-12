#include "minishell.h"

void			change_dir(char *path, int print_path, int fd_out)
{
	char	*cwd;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	dup2(fd_out, 1);
	set_env_var("OLDPWD", cwd);
    if (!chdir(path))
	{
        cwd = getcwd(buff, 4096);
		set_env_var("PWD", cwd);
		if (print_path)
			ft_putendl_fd(get_env_var("PWD"), 1);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path,1);
		if (access(path, F_OK) == -1)
			ft_putendl_fd(": no such file or directory", 1);
		else if (access(path, R_OK) == -1)
			ft_putendl_fd(": permission denied", 1);
		else
			ft_putendl_fd(": not a directory", 1);
	}
}

int	cd_builtin(char **args, int fd_out)
{
	char	*home_path;

	home_path = get_env_var("HOME");
	if (!args[0])
	{
		change_dir(home_path, 0, fd_out);
		return (1);
	}
	else
	{
		if (ft_strequ(args[0], "--"))
		{
			change_dir(home_path, 0, fd_out);
			return (1);
		}
		else if (args[0][0] == '-' && !args[0][2])
		{
			change_dir(get_env_var("OLDPWD"), 1, fd_out);
			return (1);
		}
		change_dir(args[0], 0, fd_out);
	}
	return (1);
}