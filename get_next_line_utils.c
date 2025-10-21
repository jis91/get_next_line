/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:55:42 by jeff              #+#    #+#             */
/*   Updated: 2025/10/21 13:08:27 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *src, int c)
{
	size_t	i;
	char	a;

	a = (char) c;
	i = 0;
	while (src[i])
	{
		if (src[i] == a)
			return ((char *)&src[i]);
		i++;
	}
	if (src[i] == a)
		return ((char *) &src[i]);
	return (NULL);
}


char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	total;

	total = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (total + 1));
	if (!result)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}