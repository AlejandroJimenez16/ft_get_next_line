/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:23:31 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/26 12:23:49 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*add_char(char *s, char c)
{
	int		i;
	int		size;
	char	*new_word;

	new_word = (char *)malloc((ft_strlen(s) + 2));
	if (!new_word)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	while (s[i] != '\0')
	{
		new_word[i] = s[i];
		i++;
	}
	new_word[size] = c;
	new_word[size + 1] = '\0';
	return (new_word);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	ssize_t		bytes_read;
	char		*line;
	char		*temp;
	char		*after_n;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	while (1)
	{
		if (*buffer == '\0')
		{
			bytes_read = read(fd, buffer, sizeof(buffer));
			if (bytes_read <= 0)
			{
				if (*line != '\0')
					return (temp = add_char(line, '\0'),
						free(line), line = temp, line);
				return (free(line), NULL);
			}
		}
		if (ft_strchr(buffer, '\n'))
		{
			after_n = ft_strdup(ft_strchr(buffer, '\n') + 1);
			i = 0;
			while (buffer[i] != '\0')
			{
				if (buffer[i] == '\n')
				{
					temp = add_char(line, buffer[i]);
					free(line);
					line = temp;
					ft_memset(buffer, '\0', sizeof(buffer));
					ft_strlcpy(buffer, after_n, ft_strlen(after_n));
					return (free(after_n), line);
				}
				temp = add_char(line, buffer[i]);
				free(line);
				line = temp;
				i++;
			}
		}
		temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
		ft_memset(buffer, '\0', sizeof(buffer));
	}
}
