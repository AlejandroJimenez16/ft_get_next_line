/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:23:31 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/19 17:24:26 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void add_char(char *s, char c)
{
    int i;

	i = ft_strlen(s);
    s[i] = c;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	ssize_t		bytes_read;
	char		*line;
	char		*temp;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		if (ft_strchr(buffer, '\n'))
		{
			int i = 0;
			while (buffer[i] != '\0')
			{
				if (buffer[i] == '\n')
				{
					add_char(line, '\n');
					return (line);
				}
				add_char(line, buffer[i]);
				i++;
			}
		}
		temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
		ft_memset(buffer, '\0', sizeof(buffer));
	}
	if (*line != '\0')
		return (line);
	free(line);
	return (NULL);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("quijote.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
}