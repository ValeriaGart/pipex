/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:26:22 by vharkush          #+#    #+#             */
/*   Updated: 2023/03/06 14:19:19 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"
#include "../libft/libft.h"

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
		if (!temp)
			return (NULL);
		ret = ft_strjoin(temp, command);
		free(temp);
		if (!ret)
			return (NULL);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		iter++;
	}
	return (NULL);
}

void	ft_second(t_pipex *list, char **av, char **envp)
{
	dup2(list->fd[0], STDIN_FILENO);
	close(list->fd[0]);
	close(list->fd[1]);
	dup2(list->file2, STDOUT_FILENO);
	list->args = ft_split(av[3], ' ');
	if (!(list->args == NULL))
		list->command = ft_gimme_command(list->args[0], list);
	else
		list->command = NULL;
	if (list->command == NULL || list->args == NULL)
	{
		ft_pfree(&list, 0);
		write(2, "Smth is wrong with the 2d command\n", 35);
		exit (1);
	}
	execve(list->command, list->args, envp);
}

void	ft_first(t_pipex *list, char **av, char **envp)
{
	dup2(list->fd[1], STDOUT_FILENO);
	close(list->fd[0]);
	close(list->fd[1]);
	dup2(list->file1, STDIN_FILENO);
	list->args = ft_split(av[2], ' ');
	if (!(list->args == NULL))
		list->command = ft_gimme_command(list->args[0], list);
	else
		list->command = NULL;
	if (list->command == NULL || list->args == NULL)
	{
		ft_pfree(&list, 0);
		write(2, "Smth is wrong with the 1st command\n", 35);
		exit (1);
	}
	execve(list->command, list->args, envp);
}

int	ft_do_the_magic(t_pipex	*list, char **envp, char **av)
{
	int	i;

	i = 0;
	list->pid1 = fork();
	if (list->pid1 < 0)
		i = 1;
	else if (list->pid1 == 0)
		ft_first(list, av, envp);
	list->pid2 = fork();
	if (list->pid2 < 0)
		i = 1;
	else if (list->pid2 == 0)
		ft_second(list, av, envp);
	close(list->fd[0]);
	close(list->fd[1]);
	waitpid(list->pid1, NULL, 0);
	waitpid(list->pid2, NULL, 0);
	ft_pfree(&list, 1);
	return (i);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	list;

	if (ac != 5)
		return (write(2, "Inval num of args:(\n", 20));
	list.file1 = open(av[1], O_RDONLY);
	if (list.file1 < 0)
		perror_msg("file1");
	list.file2 = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (list.file2 < 0)
		perror_msg("file2");
	if (pipe(list.fd) < 0)
		perror_msg("pipe");
	list.paths = ft_check_paths(envp);
	list.com_paths = ft_split(list.paths, ':');
	if (!list.com_paths)
	{
		close(list.file1);
		close(list.file2);
		return (1);
	}
	return (ft_do_the_magic(&list, envp, av));
}
