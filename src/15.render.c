/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15.render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:30:40 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:12:28 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_floor_at(t_game *game, int map_x, int map_y)
{
	mlx_t	*mlx;

	if (!game || !game->mlx || !game->floor.ptr)
		return ;
	mlx = (mlx_t *)game->mlx;
	mlx_image_to_window(mlx, (mlx_image_t *)game->floor.ptr,
		map_x * TILE_WIDTH, map_y * TILE_HEIGHT);
}

static void	draw_collectible_at(t_game *game, int map_x, int map_y)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			draw_x;
	int			draw_y;

	if (!game || !game->mlx || !game->collectible.ptr)
		return ;
	mlx = (mlx_t *)game->mlx;
	img = (mlx_image_t *)game->collectible.ptr;
	if (game->collectible.width <= 0 || game->collectible.height <= 0)
	{
		mlx_image_to_window(mlx, img, map_x * TILE_WIDTH, map_y * TILE_HEIGHT);
		return ;
	}
	draw_x = map_x * TILE_WIDTH + (TILE_WIDTH - game->collectible.width) / 2;
	draw_y = map_y * TILE_HEIGHT + (TILE_HEIGHT - game->collectible.height) / 2;
	mlx_image_to_window(mlx, img, draw_x, draw_y);
}

static void	draw_tile_at(t_game *game, int x, int y, char tile)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = (mlx_t *)game->mlx;
	draw_floor_at(game, x, y);
	img = get_tile_image(game, tile);
	if (!img || img == (mlx_image_t *)game->floor.ptr)
		return ;
	if (tile == 'C')
		draw_collectible_at(game, x, y);
	else if (tile == 'P')
		draw_player_image(mlx, game, img, (t_point){.x = x, .y = y});
	else
		mlx_image_to_window(mlx, img, x * TILE_WIDTH, y * TILE_HEIGHT);
}

static void	draw_player_on_top(t_game *game, mlx_t *mlx,
	mlx_image_t	*exit_img, mlx_image_t *img)
{
	int			px;
	int			py;
	char		under;

	px = game->player_x;
	py = game->player_y;
	mlx = (mlx_t *)game->mlx;
	under = game->map[py][px];
	if (px < 0 || py < 0)
		return ;
	if (under == 'E' && game->exit.ptr == game->player_exit_unlocked.ptr)
	{
		exit_img = (mlx_image_t *)game->player_exit_unlocked.ptr;
		mlx_image_to_window(mlx, exit_img, px * TILE_WIDTH, py * TILE_HEIGHT);
	}
	img = (mlx_image_t *)game->player.ptr;
	draw_player_image(mlx, game, img, (t_point){.x = px, .y = py});
}

int	render_map(t_game *game)
{
	int	y;
	int	x;

	if (!game || !game->mlx || !game->map)
		return (1);
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			draw_tile_at(game, x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
	draw_player_on_top(game, (mlx_t *)game->mlx, NULL, NULL);
	return (0);
}
