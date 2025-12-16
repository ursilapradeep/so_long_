/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12.events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:50:43 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 13:09:05 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	gfx_load_textures_part1(t_game *game)
{
	mlx_t	*mlx;
	int		rc;

	if (!game || !game->mlx)
		return (1);
	mlx = NULL;
	rc = 0;
	mlx = (mlx_t *)game->mlx;
	rc = load_png_to_img(mlx, "textures/floor.png", &game->floor);
	if (rc != 0)
	{
		write(2, "Error\nfailed to load textures/floor.png\n", 38);
		mlx_terminate(mlx);
		return (1);
	}
	rc = load_png_to_img(mlx, "textures/wall.png", &game->wall);
	if (rc != 0)
	{
		write(2, "Error\nfailed to load textures/wall.png\n", 37);
		if (game->floor.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->floor.ptr);
		mlx_terminate(mlx);
		return (1);
	}
	return (0);
}

static int	gfx_resize_player(t_game *game)
{
	int	new_w;
	int	new_h;

	if (!game || !game->player.ptr)
		return (0);
	new_w = TILE_WIDTH;
	new_h = TILE_HEIGHT;
	mlx_resize_image((mlx_image_t *)game->player.ptr, new_w, new_h);
	game->player.width = new_w;
	game->player.height = new_h;
	return (0);
}

int	gfx_load_player(t_game *game)
{
	mlx_t	*mlx;
	int		rc;

	if (!game || !game->mlx)
		return (1);
	mlx = NULL;
	rc = 0;
	mlx = (mlx_t *)game->mlx;
	rc = load_png_to_img(mlx, "textures/player.png", &game->player);
	if (rc != 0)
	{
		write(2, "Error\nfailed to load textures/player.png\n", 39);
		if (game->floor.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->floor.ptr);
		if (game->wall.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->wall.ptr);
		mlx_terminate(mlx);
		return (1);
	}
	gfx_resize_player(game);
	return (0);
}

int	gfx_load_textures_part2(t_game *game)
{
	mlx_t	*mlx;
	int		rc;

	if (!game || !game->mlx)
		return (1);
	mlx = NULL;
	rc = 0;
	mlx = (mlx_t *)game->mlx;
	rc = load_png_to_img(mlx, "textures/exit.png", &game->exit);
	if (rc != 0)
	{
		write(2, "Error\nfailed to load textures/exit.png\n", 37);
		if (game->floor.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->floor.ptr);
		if (game->wall.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->wall.ptr);
		if (game->player.ptr)
			mlx_delete_image(mlx, (mlx_image_t *)game->player.ptr);
		mlx_terminate(mlx);
		return (1);
	}
	rc = gfx_load_collectible(game);
	if (rc != 0)
		return (1);
	return (0);
}

int	setup_game_graphics(t_game *game)
{
	int		rc;

	if (!game)
		return (1);
	rc = 0;
	rc = gfx_init_window(game);
	if (rc != 0)
		return (1);
	rc = gfx_load_textures_part1(game);
	if (rc != 0)
		return (1);
	rc = gfx_load_player(game);
	if (rc != 0)
		return (1);
	rc = gfx_load_textures_part2(game);
	if (rc != 0)
		return (1);
	rc = gfx_load_exit_unlocked(game);
	if (rc != 0)
		return (1);
	return (0);
}
