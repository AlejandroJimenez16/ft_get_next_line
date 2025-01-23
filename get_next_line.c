/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:48:36 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/23 16:43:09 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	ssize_t		readed_bytes;

	if (fd == -1)
		return (NULL);
	readed_bytes = read(fd, buffer, sizeof(buffer));
	if (readed_bytes == 0)
		
	
	
}

/*
#include <stdio.h>

int main() {
    printf("El tamaño del buffer es: %d\n", BUFFER_SIZE);
    return 0;
}
*/