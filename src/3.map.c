/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:26:25 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:26:29 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_buffer_chunk(const char *buffer, ssize_t bytes_read,
	int *lines, int *last_char)
{
	ssize_t	i;

	i = 0;
	while (i < bytes_read)
	{
		if (buffer[i] == '\n')
			(*lines)++;
		*last_char = (unsigned char)buffer[i];
		i++;
	}
}

static int	validate_read_result(ssize_t bytes_read, int fd)
{
	if (bytes_read < 0)
	{
		close(fd);
		return (-1);
	}
	return (0);
}

static int	count_map_lines(char *map_path)
{
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;
	int		lines;
	int		last_char;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	last_char = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read <= 0)
			break ;
		process_buffer_chunk(buffer, bytes_read, &lines, &last_char);
	}
	if (validate_read_result(bytes_read, fd) != 0)
		return (-1);
	if (last_char != 0 && last_char != '\n')
		lines++;
	close(fd);
	return (lines);
}

static int	fill_map_array(t_game *game, char *map_path)
{
	int		fd;
	int		line_index;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (1);
	line_index = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line_index >= game->map_h)
		{
			cleanup_map_read(game, fd, line, line_index);
			return (1);
		}
		game->map[line_index] = line;
		line_index++;
		line = get_next_line(fd);
	}
	game->map[line_index] = NULL;
	close(fd);
	return (0);
}

int	open_map_file(t_game *game, char *map_path)
{
	int	lines;

	lines = count_map_lines(map_path);
	if (lines < 0)
		return (1);
	game->map_h = lines;
	game->map = (char **)malloc(sizeof(char *) * (game->map_h + 1));
	if (!game->map)
		return (1);
	if (fill_map_array(game, map_path) != 0)
	{
		free(game->map);
		game->map = NULL;
		return (1);
	}
	return (0);
}
