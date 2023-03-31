/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gimme_str_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:40:42 by vharkush          #+#    #+#             */
/*   Updated: 2023/03/06 11:40:48 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"
#include "../libft/libft.h"

void	ft_bpfree(t_pipex *list, int i)
{
	if (list->here_doc)
		unlink(".heredoc");
	while (i < list->n)
	{
		close(list->pipes[i][0]);
		close(list->pipes[i][1]);
		wait(NULL);
		i++;
	}
	i = 0;
	close(list->file1);
	close(list->file2);
	while (list->com_paths[i])
	{
		free(list->com_paths[i]);
		i++;
	}
	free(list->com_paths);
	i = 0;
	while (i < list->n)
	{
		free(list->pipes[i]);
		i++;
	}
	free(list->pipes);
}

void	ft_unlink(t_pipex *list, char **av, int perror)
{
	int	i;

	i = 0;
	if (!ft_strncmp("here_doc", av[1], 9))
		unlink(".heredoc");
	if (perror > 0)
		perror_bmsg("heredoc", 0, list, -1);
	if (perror < 0)
	{
		close(list->file1);
		close(list->file2);
	}
	if (perror <= -2)
	{
		while (list->com_paths[i])
		{
			free(list->com_paths[i]);
			i++;
		}
		free(list->com_paths);
	}
	if (perror <= -3)
		free(list->pids);
	if (perror != -4)
		exit (1);
}

int	**ft_gimme_pipes(t_pipex *list, char **av)
{
	int	**pipes;
	int	i;

	pipes = malloc(list->n * sizeof(int *));
	if (pipes == NULL)
		ft_unlink(list, av, -3);
	i = -1;
	while (++i < list->n && pipes != NULL)
	{
		pipes[i] = calloc(2, sizeof(int));
		if (pipes[i] == NULL)
		{
			if (i)
				while (--i)
					free(pipes[i]);
			if (pipes[0])
				free(pipes[0]);
			free(pipes);
			ft_unlink(list, av, -3);
		}
	}
	return (pipes);
}

void	free_pipes(int i, t_pipex *list, char **av, int exitt)
{
	if (i)
		while (--i)
			free(list->pipes[i]);
	if (list->args)
	{
		while (list->args[i])
		{
			free(list->args[i]);
			i++;
		}
		free(list->args);
	}
	if (list->pipes[0])
		free(list->pipes[0]);
	free(list->pipes);
	ft_unlink(list, av, -4);
	if (exitt > 0)
		exit (1);
}
