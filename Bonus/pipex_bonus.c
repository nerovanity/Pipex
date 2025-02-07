/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:04:39 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/06 17:20:23 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	child2(int ac, char **av, char **env, int *p_fd)
{
	int	infile;

	if (ft_strcmp(av[1], "here_doc") == 0 && ac == 6)
		here_doc(av[2]);
	else
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			close_err("No such file or directory\n", p_fd);
		if (dup2(infile, 0) == -1)
			close_err("dup failed :c\n", p_fd);
		close(infile);
	}
	if (dup2(p_fd[1], 1) == -1)
		close_err("dup failed :c\n", p_fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exe_cmd(av[3], env);
}

void	child1(int ac, char **av, char **env, int *p_fd)
{
	int	outfile;

	if (ft_strcmp(av[1], "here_doc") == 0)
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		close_err("Can't open or create the outfile file\n", p_fd);
	if (dup2(outfile, 1) == -1)
		close_err("dup failed :c\n", p_fd);
	if (dup2(p_fd[0], 0) == -1)
		close_err("dup failed :c\n", p_fd);
	close(p_fd[1]);
	close(outfile);
	close(p_fd[0]);
	exe_cmd(av[ac - 2], env);
}

void	child3(int ac, char **av, char **env, int *p_fd)
{
	int		i;
	int		fds[2];

	i = 3;
	if (i < ac - 2)
	{
		if (pipe(fds) == -1)
			close_err("somthing went wrong", p_fd);
		if (dup2(p_fd[0], fds[0]) == -1)
			close_err("dup failed :c", p_fd);
		while (i < ac - 2)
		{
			inside_cmd(ac, av, env, fds);
			i++;
		}
	}
	else
		child1(ac, av, env, p_fd);
}

void	parent(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	pid2 = 0;
	if (pid == -1)
		close_err("child 1 killed", p_fd);
	else if (!pid)
		child1(ac, av, env, p_fd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			close_err("child 2 killed", p_fd);
		else if (!pid2)
			child2(ac, av, env, p_fd);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid, NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	int	he;

	he = 0;
	if (ac < 5)
		cmd_err("./pipex infile cmd1 cmd2 ... outfile");
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			cmd_err("./pipex here_doc limiter cmd1 cmd2 ... outfile");
	}
	parent(ac, av, env);
	return (0);
}
