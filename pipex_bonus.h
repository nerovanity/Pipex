/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:55:45 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/05 16:40:05 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "./get_next_line/get_next_line.h"

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
int		is_in(const char *s, char c);
void	here_doc(char *delimiter);
void	close_err(char *str, int *p_fd);

#endif