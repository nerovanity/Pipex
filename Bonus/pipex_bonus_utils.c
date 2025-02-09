/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nero <nero@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:56:32 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/09 02:00:16 by nero             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	here_doc(char *delimiter)
{
	char	*tmp_get;
	int		fds[2];

	if (pipe(fds) == -1)
		exit(1);
	tmp_get = get_next_line(0);
	delimiter = ft_strjoin(delimiter, "\n");
	if (dup2(fds[1], 1) == -1)
		close_err("dup", fds);
	while (tmp_get && ft_strcmp(tmp_get, delimiter) != 0)
	{
		ft_putstr_fd(tmp_get, 1);
		free(tmp_get);
		tmp_get = get_next_line(0);
	}
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
}

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

void	middle(int ac, char **av, char **env, int *fds)
{
	if (dup2(fds[1], 1) == -1)
		close_err("dup2 failed :c", fds);
	close(fds[0]);
	close(fds[1]);
	exe_cmd(av[ac], env);
}

void	inside_cmd(int ac, char **av, char **env, int *fds)
{
	pid_t	pid;
	int		tmp_fd[2];

	tmp_fd[0] = fds[0];
	tmp_fd[1] = fds[1];
	if (pipe(fds) == -1)
		close_err("pipe failed", tmp_fd);
	pid = fork();
	if (pid == -1)
		close_err("fork failed", tmp_fd);
	if (pid == 0)
	{
		if (dup2(tmp_fd[0], 0) == -1)
			close_err("dup2 failed :c", tmp_fd);
		close(tmp_fd[0]);
		close(tmp_fd[1]);
		middle(ac, av, env, fds);
	}
	else
	{
		close(tmp_fd[0]);
		close(tmp_fd[1]);
	}
}
