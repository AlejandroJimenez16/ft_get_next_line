/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:23:31 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/25 16:38:35 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//get_next_line_utils
size_t	ft_strlen(const char *s)
{
	int	i;

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*str;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, (ft_strlen(s) + 1));
	return (str);
}
//--------------------------------------------------------------

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

char *add_char(char *s, char c)
{
    int	i;
	int	size;
	char *new_word;

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

char	*get_next_line(int fd)
{
	static char	buffer[10];
	ssize_t		bytes_read;
	char		*line;
	char		*temp;
	char		*after_n;
	int 		i;
	
	if (fd < 0 || 10 <= 0)
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
				{
					temp = add_char(line, '\0');
					free(line);
					line = temp;
					return (line);
				}
				free(line);
				return (NULL);
			}
		}
		//buffer[bytes_read] = '\0';
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
					free(after_n);
					return(line);
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

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("quijote.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}