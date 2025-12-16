/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.parse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:27:29 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:27:33 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_map_row(t_game *game, int y)
{
	int		x;
	char	title;

	x = 0;
	while (x < game->map_w)
	{
		title = game->map[y][x];
		if (title == 'P')
		{
			game->player_x = x;
			game->player_y = y;
		}
		else if (title == 'C')
			game->collectible_count++;
		else if (title == 'E')
			game->exit_found = 1;
		x++;
	}
}

int	parse_map_file(t_game *game)
{
	int	y;
	int	row_len;

	if (!game->map || game->map_h == 0)
		return (1);
	game->map_w = 0;
	while (game->map[0][game->map_w] != '\n'
		&& game->map[0][game->map_w] != '\0')
		game->map_w++;
	y = 0;
	game->collectible_count = 0;
	game->exit_found = 0;
	while (y < game->map_h)
	{
		row_len = 0;
		while (game->map[y][row_len] != '\n' && game->map[y][row_len] != '\0')
			row_len++;
		if (row_len != game->map_w)
			return (1);
		process_map_row(game, y);
		y++;
	}
	return (0);
}

int	load_png_to_img(mlx_t *mlx, const char *path, t_img *out)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	if (!mlx || !path || !out)
		return (1);
	tex = mlx_load_png(path);
	if (!tex)
		return (1);
	img = mlx_texture_to_image(mlx, tex);
	if (!img)
	{
		mlx_delete_texture(tex);
		return (1);
	}
	out->ptr = (void *)img;
	out->width = tex->width;
	out->height = tex->height;
	mlx_delete_texture(tex);
	return (0);
}

mlx_image_t	*get_tile_image(t_game *game, char tile)
{
	if (!game)
		return (NULL);
	if (tile == '1' && game->wall.ptr)
		return ((mlx_image_t *)game->wall.ptr);
	if (tile == '0' && game->floor.ptr)
		return ((mlx_image_t *)game->floor.ptr);
	if (tile == 'P' && game->player.ptr)
		return ((mlx_image_t *)game->player.ptr);
	if (tile == 'E' && game->exit.ptr)
		return ((mlx_image_t *)game->exit.ptr);
	if (tile == 'C' && game->collectible.ptr)
		return ((mlx_image_t *)game->collectible.ptr);
	return (NULL);
}
