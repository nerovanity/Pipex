/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:42:07 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/04 14:59:15 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *str, char c);
int		ft_strcmp(char *s1, char *s2);
void	free_array(char **tmp);
char	*get_path(char **env);
char	*ft_strdup(char *s);
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	exe_cmd(char *cmd, char **env);
int		ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split_cmd(char const *str, char c);

#endif