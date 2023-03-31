#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "./get_next_line/get_next_line.h"
#include "../libft/libft.h"

int	main(int ac, char **av)
{
	char	*buf;
	int	file;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(STDIN_FILENO);
		if (!strncmp(av[2], buf, strlen(av[2])))
			break ;
		write(file, buf, strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	unlink(".heredoc_tmp");
	return (0);
}
