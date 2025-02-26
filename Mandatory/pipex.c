/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nero <nero@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:44:43 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/09 03:14:18 by nero             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_err(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	close_err(char *str, int *p_fd)
{
	perror(str);
	close(p_fd[0]);
	close(p_fd[1]);
	exit(1);
}

void	child2(char **av, char **env, int *p_fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		close_err("infile ", p_fd);
	if (dup2(infile, 0) == -1)
		close_err("dup failed :c\n", p_fd);
	if (dup2(p_fd[1], 1) == -1)
		close_err("dup failed :c\n", p_fd);
	close(p_fd[0]);
	close(infile);
	close(p_fd[1]);
	exe_cmd(av[2], env);
}

void	child1(char **av, char **env, int *p_fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		close_err("outfile ", p_fd);
	if (dup2(outfile, 1) == -1)
		close_err("dup failed ", p_fd);
	if (dup2(p_fd[0], 0) == -1)
		close_err("dup failed ", p_fd);
	close(p_fd[1]);
	close(outfile);
	close(p_fd[0]);
	exe_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (!*env)
		cmd_err("env!\n");
	if (ac != 5)
		cmd_err("./pipex infile cmd1 cmd2 outfile\n");
	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	pid2 = 0;
	if (pid == -1)
		close_err("child 1 killed", p_fd);
	else if (!pid)
		child1(av, env, p_fd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			close_err("child 2 killed", p_fd);
		else if (!pid2)
			child2(av, env, p_fd);
	}
	return (close(p_fd[1]),close(p_fd[0]),waitpid(pid, NULL, 0), waitpid(pid2, NULL, 0), 0);
}
