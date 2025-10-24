/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:51:02 by jeff              #+#    #+#             */
/*   Updated: 2025/10/24 00:55:22 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_get_line(char *readContent);
char	*read_and_fill(int fd, char *readContent);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *src, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *src);

#endif
