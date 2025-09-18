/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:46:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/01/31 13:47:39 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*newstr;

	len = ft_strlen(s);
	newstr = malloc(len + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s, len + 1);
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resul;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	resul = malloc(len1 + len2 + 1);
	if (!resul)
		return (NULL);
	ft_strlcpy(resul, s1, len1 + 1);
	ft_strlcpy(resul + len1, s2, len2 + 1);
	return (resul);
}
