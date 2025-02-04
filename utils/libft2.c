/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:10:35 by ihamani           #+#    #+#             */
/*   Updated: 2025/02/04 13:51:41 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	ft_fill(char const *s1, char const *s2, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_fill(s1, s2, str);
	return (str);
}

int	ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	j;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return (0);
	if (len == 0)
		return (0);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		k = i;
		while (haystack[k] == needle[j] && k < len && needle[j])
		{
			k++;
			j++;
		}
		if (j == needle_len)
			return (1);
		i++;
	}
	return (0);
}
