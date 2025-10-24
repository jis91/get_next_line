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
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(read_content, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			if (read_content)
				free(read_content);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		read_content = ft_strjoin(read_content, buffer);
		if (!read_content)
		{
			free(buffer);
			return (NULL);
		}
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
	 if (!read_content[i])
        {
                free(read_content);
                return (NULL);
        }
	while (read_content[i] && read_content[i] != '\n')
		i++;
	remaining_content = (char *)malloc(sizeof(char)
			* (ft_strlen(read_content) - i + 1));
	if (!remaining_content)
	{
		free(remaining_content);
		if (read_content)
			free(read_content);
		return (NULL);
	}
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
	static char	*read_content;
	char		*line;

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
/*
int	main(void)
{
	char	*line;
	int		fd1;
	int		fd2;
	int		fd3;
	int		empty_fd;

	fd1 = open("test.txt", O_RDONLY);
	printf("=== TESTING fd1 ===\n");
	while ((line = get_next_line(fd1)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd1);
	fd2 = open("test2.txt", O_RDONLY);
	printf("=== TESTING fd2 ===\n");
        while ((line = get_next_line(fd2)))
        {
                printf("%s\n", line);
                free(line);
        }
	close(fd2);
        fd3 = open("test3.txt", O_RDONLY);
	printf("=== TESTING fd3 ===\n");
        while ((line = get_next_line(fd3)))
        {
                printf("%s\n", line);
                free(line);
        }
	close(fd3);
        empty_fd = open("empty.txt", O_RDONLY);
	printf("=== TESTING empty fd ===\n");
   	while ((line = get_next_line(empty_fd)))
        {
                printf("%s\n", line);
                free(line);
        }	
	close(empty_fd);
	return (0);
}*/
