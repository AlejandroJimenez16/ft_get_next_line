#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
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

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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

static char *add_char(char *s, char c) {
    (void)s;
    (void)c;
    return NULL; // Fuerza el fallo
}

static int	buffer_is_empty(int fd, char *buffer, char **line)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	if (bytes_read == 0)
	{
		if (*line && **line != '\0')
		{
			temp = add_char(*line, '\0');
			if (!temp)
				return (free(*line), *line = NULL, 0);
			return (free(*line), *line = temp, 0);
		}
		return (free(*line), *line = NULL, 0);
	}
	return (1);
}

static char	*n_in_buffer(char *buffer, char *line)
{
	char	*after_n;
	int		i;
	char	*temp;

	if (!ft_strchr(buffer, '\n'))
		return (NULL);
	after_n = ft_strdup(ft_strchr(buffer, '\n') + 1);
	if (!after_n)
		return (NULL);
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
		return (free(line), line = temp, ft_memset(buffer, '\0', BUFFER_SIZE),
			ft_strlcpy(buffer, after_n, ft_strlen(after_n)), free(after_n),
			line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	char		*temp;

	if (fd < 0)
		return (NULL);
	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	while (1)
	{
		if (*buffer == '\0')
		{
			if (buffer_is_empty(fd, buffer, &line) == 0)
				return (line);
		}
		if (ft_strchr(buffer, '\n'))
			return (n_in_buffer(buffer, line));
		temp = ft_strjoin(line, buffer);
		if (!temp)
			return (free(line), NULL);
		free(line);
		line = temp;
		ft_memset(buffer, '\0', BUFFER_SIZE);
	}
}

int main() {
    int pipefd[2];
    pipe(pipefd);

    // Escribir una cadena en el pipe
    write(pipefd[1], "Hola\n", 5);

    // Simular fallo de malloc en add_char
    char *line = get_next_line(pipefd[0]);

    if (line == NULL) {
        printf("get_next_line devolvió NULL correctamente.\n");
    } else {
        printf("get_next_line devolvió: %s\n", line);
        free(line); // Liberar la memoria aquí
    }

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}