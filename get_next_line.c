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

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;
	char		*newline;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	while (1)
	{
		
	}
	
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
}
