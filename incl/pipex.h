/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:30:20 by vharkush          #+#    #+#             */
/*   Updated: 2023/02/23 16:34:51 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		file1;
	int		file2;
	char	*paths;
	char	*command;
	char	**args;
	char	**com_paths;
}	t_pipex;

void	perror_msg(char *error);
void	ft_pfree(t_pipex **list, int pid);
char	*ft_check_paths(char **envp);

#endif
