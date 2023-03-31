/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:36:14 by vharkush          #+#    #+#             */
/*   Updated: 2023/03/03 17:36:16 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include "../get_next_line/get_next_line.h"

typedef struct s_pipex
{
	pid_t	*pids;
	int		n;
	int		file1;
	int		file2;
	int		**pipes;
	int		here_doc;
	char	*paths;
	char	*command;
	char	**args;
	char	**com_paths;
}	t_pipex;

void	perror_bmsg(char *error, int j, t_pipex *list, int i);
void	ft_bpfree(t_pipex *list, int i);
void	ft_check_child(int i, t_pipex *list);
void	ft_unlink(t_pipex *list, char **av, int perror);
void	free_pipes(int i, t_pipex *list, char **av, int exitt);
char	*ft_bcheck_paths(char **envp);
char	*ft_gimme_command(char *command, t_pipex *list);
int		**ft_gimme_pipes(t_pipex *list, char **av);

#endif
