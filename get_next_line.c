/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:23:31 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/19 15:54:56 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	origin_size_dst;
	size_t	origin_size_src;

	origin_size_dst = ft_strlen(dst);
	origin_size_src = ft_strlen(src);
	if (size <= origin_size_dst)
		return (size + origin_size_src);
	i = 0;
	while (src[i] != '\0' && i < size - origin_size_dst - 1)
	{
		dst[origin_size_dst + i] = src[i];
		i++;
	}
	dst[origin_size_dst + i] = '\0';
	return (origin_size_dst + origin_size_src);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((unsigned char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
*/
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	ssize_t		bytes_read;
	char		*line;
	
	line = calloc(200, 1);
	if (fd == -1)
		return (NULL);
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	return (0);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
