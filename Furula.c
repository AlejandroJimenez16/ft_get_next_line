
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
	static char	buffer[100 + 1]; // +1 para '\0'
	char		*line;
	char		*newline;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	while (1)
	{
		// Leer solo si el buffer está vacío
		if (*buffer == '\0')
		{
			bytes_read = read(fd, buffer, 100);
			if (bytes_read <= 0)
				return (*line ? line : (free(line), NULL)); // Evita fugas de memoria
			buffer[bytes_read] = '\0';
		}
		// Buscar el salto de línea
		newline = ft_strchr(buffer, '\n');
		if (newline)
		{
			*newline = '\0';
			char *temp = ft_strjoin(line, buffer);
			free(line);
			line = temp;
			ft_strcpy(buffer, newline + 1); // Guardar el resto del buffer
			return (line);
		}
		// Si no hay '\n', añadir el buffer actual a la línea y vaciarlo
		char *temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
		*buffer = '\0'; // Vaciar el buffer para la próxima lectura
	}
	return (NULL);
}