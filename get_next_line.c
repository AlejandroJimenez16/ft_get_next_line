/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:48:36 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/29 16:26:40 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	ssize_t		readed_bytes;
	int			i;
	int			size_line;
	char 		*line;	

	if (fd == -1)
		return (NULL);
	readed_bytes = read(fd, buffer, sizeof(buffer));
	if (readed_bytes <= 0)
		return (NULL);
	while (readed_bytes > 0)
	{
		
		size_line = 0;
		while (size_line < readed_bytes && buffer[size_line] != '\n')
			size_line++;
		line = (char *)malloc((size_line + 1) * sizeof(char));
		if (!line)
			return (NULL);
		i = 0;
		while (i < size_line)
		{
			line[i] = buffer[i];
			i++;
		}
		readed_bytes = read(fd, buffer, sizeof(buffer));
	}
	line[i] = '\n';
	return (line);
}

#include <stdio.h>

int main(void)
{
	char *line;
	int fd;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return (0);

}
