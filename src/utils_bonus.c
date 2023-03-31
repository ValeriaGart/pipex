/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:35:06 by vharkush          #+#    #+#             */
/*   Updated: 2023/03/03 17:35:08 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"
#include "../libft/libft.h"

void	ft_check_child(int i, t_pipex *list)
{
	if (i == 0)
	{
		dup2(list->pipes[i + 1][1], STDOUT_FILENO);
		close(list->pipes[i][0]);
		close(list->pipes[i + 1][1]);
		dup2(list->file1, STDIN_FILENO);
	}
	else if (i != list->n - 1 && i != 0)
	{
		dup2(list->pipes[i + 1][1], STDOUT_FILENO);
		dup2(list->pipes[i][0], STDIN_FILENO);
		close(list->pipes[i][0]);
		close(list->pipes[i + 1][1]);
	}
	else
	{
		dup2(list->pipes[i][0], STDIN_FILENO);
		close(list->pipes[i][0]);
		dup2(list->file2, STDOUT_FILENO);
	}
}

char	*ft_bcheck_paths(char **envp)
{
	while (envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			return (*envp + 5);
		envp++;
	}
	write(2, "Path not found in envs\n", 23);
	exit(1);
}

void	perror_bmsg(char *error, int j, t_pipex *list, int i)
{
	if (i == -1)
	{
		perror(error);
		exit (1);
	}
	while (j < list->n)
	{
		if (i != j)
			close(list->pipes[j][0]);
		if (i + 1 != j)
			close(list->pipes[j][1]);
		j++;
	}
}

char	*ft_gimme_command(char *command, t_pipex *list)
{
	char	*temp;
	char	*ret;
	char	**iter;

	if (!command)
		return (NULL);
	iter = list->com_paths;
	while (*iter)
	{
		temp = ft_strjoin(*iter, "/");
		ret = ft_strjoin(temp, command);
		free(temp);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		iter++;
	}
	return (NULL);
}
