/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:56:32 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/05 16:40:01 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	here_doc(char *delimiter)
{
	char	*str;
	char	*tmp;
	char	*tmp_get;

	str = NULL;
	tmp_get = get_next_line(0);
	delimiter = ft_strjoin(delimiter, "\n");
	while (tmp_get && ft_strcmp(tmp_get, delimiter) != 0)
	{
		tmp = str;
		str = ft_strjoin(str, tmp_get);
		free(tmp);
		free(tmp_get);
		tmp_get = get_next_line(0);
	}
	if (str)
		ft_putstr_fd(str, 1);
	free(delimiter);
	free(str);
}
