#include "get_next_line.h"

char    *read_and_fill(int fd, char *readContent)
{
    char    *buffer;
    int     bytes_read;

    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while (bytes_read != 0 && !ft_strchr(readContent, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        readContent = ft_strjoin(readContent, buffer);
    }
    free(buffer);
    return (readContent);
}

char    *get_line(char *readContent)
{
    int     i;
    char    *str;

    i = 0;
    if (!readContent[i])
        return (NULL);
    while (readContent[i] && readContent != '\n')
        i++;
    str = malloc(sizeof(char) * i + 2);
    if (!str)
        return (NULL);
    i = 0;
    while (readContent[i] && readContent != '\n')
    {
        str[i] = readContent[i];
        i++;
    }
    if (readContent[i] == '\n')
    {
        str[i] = readContent[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

char	*get_next_line(int fd)
{
    static char  *readContent[BUFFER_SIZE + 1];
    char *line;

    if (read(fd, readContent, 0) < 0)
        return (NULL);
    readContent = read_and_fill(fd, readContent);
    if (!readContent)
        return (NULL);
    line = get_line(readContent);
    return (line);
}

