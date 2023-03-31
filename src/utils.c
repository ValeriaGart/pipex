/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:29:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/03/06 14:20:38 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"
#include "../libft/libft.h"

char	*ft_check_paths(char **envp)
{
	while (envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			return (*envp + 5);
		envp++;
	}
	write(2, "Path not found in envs\n", 23);
	exit (1);
}

void	perror_msg(char *error)
{
	perror(error);
	exit (1);
}

void	ft_pfree(t_pipex **list, int pid)
{
	int	i;

	i = 0;
	close((*list)->file1);
	close((*list)->file2);
	while ((*list)->com_paths[i])
	{
		free((*list)->com_paths[i]);
		i++;
	}
	free((*list)->com_paths);
	i = 0;
	if (pid == 1)
		return ;
	if ((*list)->args != NULL)
	{
		while ((*list)->args[i])
		{
			free((*list)->args[i]);
			i++;
		}
		free((*list)->args);
	}
	if ((*list)->command != NULL)
		free((*list)->command);
}
