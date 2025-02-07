/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:35:52 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/07 10:46:06 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*get_path(char **env)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	tmp = ft_split(env[i], '=');
	while (env[i])
	{
		if (tmp && ft_strcmp("PATH", tmp[0]) == 0)
			break ;
		free_array(tmp);
		tmp = ft_split(env[i++], '=');
	}
	if (ft_strcmp("PATH", tmp[0]) == 0)
		path = ft_strdup(tmp[1]);
	else
		path = NULL;
	free_array(tmp);
	return (path);
}
