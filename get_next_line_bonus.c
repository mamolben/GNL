/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:45:49 by marimoli          #+#    #+#             */
/*   Updated: 2025/01/31 13:46:36 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_line(char *line_str)
{
	size_t	len;
	char	*line;

	len = 0;
	while (line_str[len] && line_str[len] != '\n')
		len++;
	line = malloc(len + 1 + (line_str[len] == '\n'));
	if (!line)
		return (NULL);
	ft_strlcpy(line, line_str, len + 1);
	if (line_str[len] == '\n')
		line[len] = '\n';
	line[len + (line_str[len] == '\n')] = '\0';
	return (line);
}

static char	*ft_update_str(char *line_str)
{
	size_t	i;
	char	*new_str;

	i = 0;
	while (line_str[i] && line_str[i] != '\n')
		i++;
	if (!line_str[i])
	{
		free(line_str);
		return (NULL);
	}
	new_str = malloc(ft_strlen(line_str) - i);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, line_str + i + 1, ft_strlen(line_str) - i);
	free(line_str);
	return (new_str);
}

static char	*ft_fd_read(int fd, char *line_str)
{
	char	buf[BUFFER_SIZE + 1];
	size_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	if (!line_str)
		line_str = ft_strdup("");
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(line_str, buf);
		if (!tmp)
		{
			free(line_str);
			return (NULL);
		}
		free(line_str);
		line_str = tmp;
		if (ft_strchr(line_str, '\n'))
			break ;
	}
	return (line_str);
}

char	*get_next_line(int fd)
{
	static char	*line_str[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	line_str[fd] = ft_fd_read(fd, line_str[fd]);
	if (!line_str[fd] || line_str[fd][0] == '\0')
	{
		free(line_str[fd]);
		line_str[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(line_str[fd]);
	if (!line)
	{
		free(line_str[fd]);
		line_str[fd] = NULL;
		return (NULL);
	}
	line_str[fd] = ft_update_str(line_str[fd]);
	return (line);
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	int		fd2;
	int		fd3;
	char	*line1;
	char	*line2;
	char	*line3;

	fd = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	if ((fd < 0) || (fd2 < 0) || (fd3 < 0))
	{
		perror("Error opening file");
		return (1);
	}
	line1 = get_next_line(fd);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	while ((line1 != NULL) || (line2 != NULL) || (line3 != NULL))
	{
		if (line1 != NULL)
		{
			printf("File 1: %s", line1);
			free(line1);
			line1 = get_next_line(fd);
		}
		if (line2 != NULL)
		{
			printf("File 2: %s", line2);
			free(line2);
			line2 = get_next_line(fd2);
		}
		if (line3 != NULL)
		{
			printf("File 3: %s\n", line3);
			free(line3);
			line3 = get_next_line(fd3);
		}
	}
	close(fd);
	close(fd2);
	close(fd3);
	return (0);	
}
