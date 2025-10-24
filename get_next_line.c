/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:50:55 by jeff              #+#    #+#             */
/*   Updated: 2025/10/24 02:12:27 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_and_fill(int fd, char *read_content)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(read_content, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(read_content, buffer);
		if (!tmp)  // If memory allocation for the new string failed, free buffer and return NULL
        {
            free(buffer);
            free(read_content);
            return (NULL);
        }
		free (read_content);
		read_content = tmp;
	}
	free(buffer);
	return (read_content);
}

char	*ft_get_line(char *read_content)
{
	int		i;
	char	*str;

	i = 0;
	if (!read_content[i])
		return (NULL);
	while (read_content[i] && read_content[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (read_content[i] && read_content[i] != '\n')
	{
		str[i] = read_content[i];
		i++;
	}
	if (read_content[i] == '\n')
	{
		str[i] = read_content[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_remaining_content(char *read_content)
{
	int		i;
	int		j;
	char	*remaining_content;

	i = 0;
	j = 0;
	while (read_content[i] && read_content[i] != '\n')
		i++;
	if (read_content[i] == '\n')
		i++;
	remaining_content = malloc(sizeof(char) * (ft_strlen(read_content) - i + 1));
	if (!remaining_content)
		return (NULL);
	while (read_content[i])
	{
		remaining_content[j] = read_content[i];
		i++;
		j++;
	}
	remaining_content[j] = '\0';
	return (remaining_content);
}

char	*initial_check(int fd, char *read_content)
{
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (read_content == NULL)
	{
		read_content = malloc(sizeof(char));
		if (!read_content)
			return (NULL);
		read_content[0] = '\0';
	}
	return (read_content);
}

char	*get_next_line(int fd)
{
	static char	*read_content = NULL;
	char		*line;
	char		*remaining_content;

	initial_check(fd, read_content);
	read_content = read_and_fill(fd, read_content);
	if (!read_content)
		return (NULL);
	line = ft_get_line(read_content);
	if (!line)
		return (NULL);
	remaining_content = get_remaining_content(read_content);
	if (!remaining_content)
		return (NULL);
	free(read_content);
	read_content = remaining_content;
	return (line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	int		empty_fd;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	empty_fd = open("empty.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line %d: %s\n", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line %d: %s\n", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line %d: %s\n", i, line);
		free(line);
		line = get_next_line(empty_fd);
		printf("line %d: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(empty_fd);
	return (0);
}
