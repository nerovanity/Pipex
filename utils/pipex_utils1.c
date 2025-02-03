/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:06:18 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/03 15:43:06 by ihamani          ###   ########.fr       */
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
		if (!access(tmp, F_OK | X_OK))
			return (free_array(paths), tmp);
		free(tmp);
		i++;
	}
	free_array(paths);
	return (NULL);
}

// char	*get_cmd(char **full_cmd, char **env)
// {
// 	char	*cmd;
// 	char	*flag;
// 	char	*cmd_path;
// 	char	*path;

// 	cmd = full_cmd[0];
// 	free_array(full_cmd);
// 	cmd_path = ft_strjoin("/", cmd);
// 	path = check_cmd(cmd_path, env);
// 	free(cmd_path);
// 	return (path);
// }

void	exe_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	cmd = ft_strjoin("/", s_cmd[0]);
	path = check_cmd(cmd, env);
	free(cmd);
	if (path == NULL)
	{
		ft_putstr_fd("no command found", 2);
		exit(1);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(s_cmd[0], 2);
		free(path);
		free_array(s_cmd);
		exit(1);
	}
	free(path);
	free_array(s_cmd);
}

