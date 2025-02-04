/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:18 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/04 15:52:53 by ihamani          ###   ########.fr       */
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
	perror("command not found");
	exit(1);
}

char	*check_local(char *cmd)
{
	if (!access(cmd, X_OK))
		return (cmd);
	return (NULL);
}

void	exe_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split_cmd(cmd, ' ');
	if (ft_strnstr(s_cmd[0], "./", ft_strlen(s_cmd[0])))
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
