#include "minishell.h"

char	**ft_argv_dup(char **argv)
{
	char	**heap;
	int		len;

	len = ft_argc(argv);
	heap = ft_calloc(len + 1, sizeof(*heap));
	if (!heap)
		ft_perrno_exit(ERR_SYS_MALLOC);
	len = -1;
	while (argv[++len])
	{
		heap[len] = ft_strdup(argv[len]);
		if (!heap[len])
			ft_perrno_exit(ERR_SYS_MALLOC);
	}
	return (heap);
}
