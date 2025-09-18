/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:35:36 by marimoli          #+#    #+#             */
/*   Updated: 2025/02/04 18:01:17 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *line_str)
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

char	*ft_update_str(char *line_str)
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
	static char	*line_str = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_str = ft_fd_read(fd, line_str);
	if (!line_str || line_str[0] == '\0')
	{
		free(line_str);
		line_str = NULL;
		return (NULL);
	}
	line = ft_get_line(line_str);
	if (!line)
	{
		free(line_str);
		line_str = NULL;
		return (NULL);
	}
	line_str = ft_update_str(line_str);
	return (line);
}

//#include <stdio.h>

/*int	main(void)
{
	int		fd;
	int		line_count;
	char	*gnl;

	line_count = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		line_count++;
		printf("[%d]:%s", line_count, gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
	return (0);
}*/

/*
 int	main(void)
{
	char	*str;

	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (str == NULL)
			break ;
		printf("%s ", str);
		printf("ctrl C para salir \n");
		free (str);
	}
	return (0);
} */