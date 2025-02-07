/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:56:32 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/06 17:00:03 by ihamani          ###   ########.fr       */
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
	dup2(fds[1], 1);
	while (tmp_get && ft_strcmp(tmp_get, delimiter) != 0)
	{
		ft_putstr_fd(tmp_get, 1);
		free(tmp_get);
		tmp_get = get_next_line(0);
	}
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	close(1);
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

void	middle(int ac, char **av, char**env, int *fds)
{
	if (dup2(fds[1], 1) == -1)
		close_err("dup failed :c\n", fds);
	if (dup2(fds[0], 0) == -1)
		close_err("dup failed :c\n", fds);
	exe_cmd(av[ac - 2], env);
}

void	inside_cmd(int ac, char **av, char **env, int *fds)
{
	pid_t	pid;
	int		tmp;

	close(fds[1]);
	tmp = fds[0];
	if (pipe(fds) == -1)
		close_err("somthing went wrong", fds);
	if (dup2(tmp, fds[0]) == -1)
		close_err("dup failed :c", fds);
	pid = fork();
	if (pid)
		middle(ac, av, env, fds);
}
