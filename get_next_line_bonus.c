/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:39:26 by alejandj          #+#    #+#             */
/*   Updated: 2025/03/05 12:29:40 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*add_char(char *s, char c)
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

static int	buffer_is_empty(int fd, char *buffer, char **line)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
		buffer[bytes_read] = '\0';
	if (bytes_read == -1)
		return (free(*line), *line = NULL, 0);
	if (bytes_read == 0)
	{
		if (**line != '\0')
		{
			temp = add_char(*line, '\0');
			free(*line);
			*line = temp;
			return (0);
		}
		free(*line);
		*line = NULL;
		return (0);
	}
	return (1);
}

static char	*n_in_buffer(char *buffer, char *line)
{
	char	*after_n;
	int		i;
	char	*temp;

	after_n = ft_strdup(ft_strchr(buffer, '\n') + 1);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		temp = add_char(line, buffer[i]);
		free(line);
		line = temp;
		i++;
	}
	if (buffer[i] == '\n')
	{
		temp = add_char(line, buffer[i]);
		free(line);
		line = temp;
		ft_memset(buffer, '\0', BUFFER_SIZE);
		ft_strlcpy(buffer, after_n, ft_strlen(after_n));
		free(after_n);
		return (line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	line = ft_strdup("");
	while (1)
	{
		if (*buffer[fd] == '\0' && buffer_is_empty(fd, buffer[fd], &line) == 0)
			return (free(buffer[fd]), buffer[fd] = NULL, line);
		if (ft_strchr(buffer[fd], '\n'))
			return (n_in_buffer(buffer[fd], line));
		temp = ft_strjoin(line, buffer[fd]);
		free(line);
		line = temp;
		ft_memset(buffer[fd], '\0', BUFFER_SIZE);
	}
}
