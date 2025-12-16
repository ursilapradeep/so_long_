/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14.collectible.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:40:24 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:00:39 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	gfx_resize_collectible(t_game *game)
{
	int		new_w;
	int		new_h;

	if (!game || !game->collectible.ptr)
		return (0);
	new_w = TILE_WIDTH / 2;
	new_h = TILE_HEIGHT / 2;
	mlx_resize_image((mlx_image_t *)game->collectible.ptr, new_w, new_h);
	game->collectible.width = new_w;
	game->collectible.height = new_h;
	return (0);
}

int	gfx_load_collectible(t_game *game)
{
	mlx_t	*mlx;
	int		rc;

	if (!game || !game->mlx)
		return (1);
	mlx = NULL;
	rc = 0;
	mlx = (mlx_t *)game->mlx;
	rc = load_png_to_img(mlx, "textures/collectible.png", &game->collectible);
	if (rc != 0)
	{
		write(2, "Error\nfailed to load textures/collectible.png\n", 45);
		if (game->floor.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->floor.ptr);
		if (game->wall.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->wall.ptr);
		if (game->player.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->player.ptr);
		if (game->exit.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->exit.ptr);
		mlx_terminate(mlx);
		return (1);
	}
	gfx_resize_collectible(game);
	return (0);
}

static void	gfx_resize_exit_unlocked(t_game *game)
{
	if (!game || !game->player_exit_unlocked.ptr)
		return ;
	mlx_resize_image((mlx_image_t *) game->player_exit_unlocked.ptr,
		TILE_WIDTH, TILE_HEIGHT);
	game->player_exit_unlocked.width = TILE_WIDTH;
	game->player_exit_unlocked.height = TILE_HEIGHT;
}

int	gfx_load_exit_unlocked(t_game *game)
{
	mlx_t	*mlx;
	int		rc;

	if (!game || !game->mlx)
		return (1);
	mlx = (mlx_t *)game->mlx;
	rc = load_png_to_img(mlx, "textures/exit_unlocked.png",
			&game->player_exit_unlocked);
	if (rc != 0)
	{
		write(2, "Error\nfailed to load textures/exit_unlocked.png\n", 47);
		if (game->floor.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->floor.ptr);
		if (game->wall.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->wall.ptr);
		if (game->player.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->player.ptr);
		if (game->exit.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->exit.ptr);
		mlx_terminate(mlx);
		return (1);
	}
	gfx_resize_exit_unlocked(game);
	return (0);
}

void	draw_player_image(mlx_t *mlx, t_game *game,
	mlx_image_t *img, t_point pos)
{
	int	draw_x;
	int	draw_y;

	if (!game || !mlx || !img)
		return ;
	if (game->player.width > 0 && game->player.height > 0)
	{
		draw_x = pos.x * TILE_WIDTH + (TILE_WIDTH - game->player.width) / 2;
		draw_y = pos.y * TILE_HEIGHT + (TILE_HEIGHT - game->player.height) / 2;
		mlx_image_to_window(mlx, img, draw_x, draw_y);
	}
	else
		mlx_image_to_window(mlx, img, pos.x * TILE_WIDTH, pos.y * TILE_HEIGHT);
}
