/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:22:45 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/28 15:24:21 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*read_and_fill(int fd, char *read_content)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(read_content), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (read_content && ft_strchr(read_content, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(read_content), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		read_content = ft_strjoin(read_content, buffer);
		if (!read_content)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (read_content);
}

static char	*ft_get_line(char *read_content)
{
	int		i;
	char	*line;

	i = 0;
	if (!read_content[i])
		return (NULL);
	while (read_content[i] && read_content[i] != '\n')
		i++;
	if (read_content[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (read_content[i] && read_content[i] != '\n')
	{
		line[i] = read_content[i];
		i++;
	}
	if (read_content[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*get_remaining_content(char *read_content)
{
	int		i;
	int		j;
	char	*remaining_content;

	i = 0;
	if (!read_content)
		return (NULL);
	while (read_content[i] && read_content[i] != '\n')
		i++;
	if (!read_content[i])
		return (free(read_content), NULL);
	remaining_content = (char *)malloc(sizeof(char)
			* (ft_strlen(read_content) - i + 1));
	if (!remaining_content)
		return (free(remaining_content), free(read_content), NULL);
	i++;
	j = 0;
	while (read_content[i])
		remaining_content[j++] = read_content[i++];
	remaining_content[j] = '\0';
	free(read_content);
	return (remaining_content);
}

char	*get_next_line(int fd)
{
	static char	*read_content[MAX_FD];
	char		*line;
	char		*buffer;

    buffer = (char *)malloc(BUFFER_SIZE + 1) * sizeof(char);
    if (!buffer)
        return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_content == NULL)
	{
		read_content = (char *)malloc(sizeof(char));
		if (!read_content)
			return (NULL);
		read_content[0] = '\0';
	}
	read_content = read_and_fill(fd, read_content);
	if (!read_content)
		return (NULL);
	line = ft_get_line(read_content);
	if (!line)
	{
		free(read_content);
		read_content = NULL;
		return (NULL);
	}
	read_content = get_remaining_content(read_content);
	return (line);
}
