#include "minishell.h"

char	**ft_exec_env_path_split(t_shell *shell)
{
	char	*env_path;
	char	**path_dirs;

	env_path = ft_getenv(shell, "PATH");
	if (!env_path)
		return (NULL);
	path_dirs = ft_split(env_path, ':');
	if (!path_dirs)
		ft_perror_exit(ERR_SYS_MALLOC);
	return (path_dirs);
}

char	*ft_exec_src_path(char **path, char *arg)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				i;
	int				arg_len;

	arg_len = ft_strlen(arg);
	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir)
		{
			while (1)
			{
				dirent = readdir(dir);
				if (!dirent)
					break ;
				else
				{
					if (!ft_memcmp(dirent->d_name, arg, arg_len)
						&& !dirent->d_name[arg_len])
					{
						closedir(dir);
						return (path[i]);
					}
				}
			}
			closedir(dir);
		}
	}
	return (NULL);
}

void	ft_exec_env_path(t_shell *shell, char **arg)
{
	char	**path;
	char	*dir;
	int		i;

	path = ft_exec_env_path_split(shell);
	if (!path)
		return ;
	dir = ft_exec_src_path(path, *arg);
	if (!dir)
		return (ft_gc_arr_str(path));
	ft_printf("%s/%s\n", dir, *arg);
	ft_gc_arr_str(path);
}
