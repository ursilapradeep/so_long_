/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.get_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:26:42 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:26:47 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!src && !dst)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

static char	*read_and_append(int fd, char *buffer, char *line, int *bytes_read)
{
	char	*temp;

	*bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && *bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			buffer[0] = '\0';
			return (free(line), NULL);
		}
		if (*bytes_read > 0)
		{
			buffer[*bytes_read] = '\0';
			temp = ft_strjoin(line, buffer);
			if (!temp)
				return (free(line), NULL);
			free(line);
			line = temp;
		}
	}
	return (line);
}

static char	*extract_line(char *line)
{
	size_t		len;

	if (!line)
		return (NULL);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] == '\n')
		return (ft_substr(line, 0, len + 1));
	return (ft_strdup(line));
}

static void	updated_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		while (buffer[i])
			buffer[j++] = buffer[i++];
	}
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*new_buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	line = ft_strdup(buffer);
	if (!line)
		return (NULL);
	line = read_and_append(fd, buffer, line, &bytes_read);
	if (!line)
		return (NULL);
	if (bytes_read == 0 && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	new_buffer = extract_line(line);
	updated_buffer(buffer);
	free(line);
	return (new_buffer);
}
