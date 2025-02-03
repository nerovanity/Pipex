/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:44:43 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/03 15:15:38 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_err(void)
{
	ft_putstr_fd("./pipex file1 cmd1 cmd2 file2", 2);
	exit(1);
}

void	child2(char **av, char **env, int *p_fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		ft_putstr_fd("infile doesn't exist", 2);
		exit(1);
	}
	dup2(infile, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exe_cmd(av[2], env);
}

void	child1(char **av, char **env, int *p_fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT);
	dup2(outfile, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exe_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (ac != 5)
		cmd_err();
	pid = 0;
	pid2 = 0;
	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	if (!pid)
	{
		pid2 = fork();
		if (!pid2)
			child2(av, env, p_fd);
		child1(av, env, p_fd);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	return (waitpid(pid, NULL, 0), waitpid(pid2, NULL, 0), 0);
}

