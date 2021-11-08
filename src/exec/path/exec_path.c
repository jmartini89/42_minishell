/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:12 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:13 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **
	ft_exec_path_split(t_shell *shell)
{
	char	*env_path;
	char	**path_dirs;

	env_path = ft_getenv(shell, "PATH");
	if (!env_path)
		return (NULL);
	path_dirs = ft_split(env_path, ':');
	if (!path_dirs)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	return (path_dirs);
}

static int
	ft_exec_src_file(DIR *dir, char *arg)
{
	struct dirent	*dirent;
	int				arg_len;

	arg_len = ft_strlen(arg);
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		else
		{
			if (!ft_memcmp(dirent->d_name, arg, arg_len)
				&& !dirent->d_name[arg_len])
				return (1);
		}
	}
	return (0);
}

char
	*ft_exec_src_dir(char **path, char *arg)
{
	DIR	*dir;
	int	i;

	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (dir)
		{
			if (ft_exec_src_file(dir, arg))
			{
				closedir(dir);
				return (path[i]);
			}
			closedir(dir);
		}
	}
	return (NULL);
}

int
	ft_exec_env_path(t_shell *shell, char **arg)
{
	char	**path;
	char	*dir;
	char	*dir_heap;
	char	*tmp;

	path = ft_exec_path_split(shell);
	if (!path)
		return (0);
	dir = ft_exec_src_dir(path, *arg);
	if (!dir)
	{
		ft_gc_2p_str(path);
		return (0);
	}
	dir_heap = ft_strjoin(dir, "/");
	if (!dir_heap)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	tmp = *arg;
	*arg = ft_strjoin(dir_heap, *arg);
	free (dir_heap);
	free (tmp);
	ft_gc_2p_str(path);
	return (1);
}
