/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nero <nero@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:18 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/08 23:52:08 by nero             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*check_cmd(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	int		i;
	char	*tmp;

	i = 0;
	path_env = get_path(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (!access(tmp, X_OK))
			return (free_array(paths), tmp);
		free(tmp);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	check_path(char *path, char **s_cmd)
{
	free(path);
	free_array(s_cmd);
	ft_putstr_fd("command not found\n", 2);
	exit(1);
}

char	*check_local(char *cmd)
{
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	return (NULL);
}

void	exe_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!env)
		exit(1);
	if (!cmd[0] || !cmd)
		exit(1);
	s_cmd = ft_split_cmd(cmd, ' ');
	if (ft_strnstr(s_cmd[0], "./", ft_strlen(s_cmd[0])))
		path = check_local(s_cmd[0]);
	else if (is_in(s_cmd[0], '/'))
		path = check_local(s_cmd[0]);
	else
	{
		cmd = ft_strjoin("/", s_cmd[0]);
		path = check_cmd(cmd, env);
		if (cmd)
			free(cmd);
	}
	if (path == NULL)
		check_path(path, s_cmd);
	if (execve(path, s_cmd, env) == -1)
		check_path(path, s_cmd);
	free(path);
	free_array(s_cmd);
}
