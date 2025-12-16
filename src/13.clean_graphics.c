/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13.clean_graphics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:03:05 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 12:16:20 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	gfx_init_window(t_game *game)
{
	int		win_w;
	int		win_h;
	mlx_t	*mlx;

	if (!game)
		return (1);
	win_w = game->map_w * TILE_WIDTH;
	win_h = game->map_h * TILE_HEIGHT;
	mlx = mlx_init(win_w, win_h, "so_long", false);
	if (!mlx)
	{
		ft_putendl_fd("Error\nfailed to create window", 2);
		return (1);
	}
	game->mlx = (void *)mlx;
	game->window = NULL;
	return (0);
}

static	void	cleanup_images_part1(t_game *game, mlx_t *mlx)
{
	if (!game || !mlx)
		return ;
	if (game->floor.ptr)
	{
		mlx_delete_image(mlx, (mlx_image_t *)game->floor.ptr);
		game->floor.ptr = NULL;
		game->floor.width = 0;
		game->floor.height = 0;
	}
	if (game->wall.ptr)
	{
		mlx_delete_image(mlx, (mlx_image_t *)game->wall.ptr);
		game->wall.ptr = NULL;
		game->wall.width = 0;
		game->wall.height = 0;
	}
}

static	void	cleanup_images_part2(t_game *game, mlx_t *mlx)
{
	if (!game || !mlx)
		return ;
	if (game->player.ptr)
	{
		mlx_delete_image(mlx, (mlx_image_t *)game->player.ptr);
		game->player.ptr = NULL;
		game->player.width = 0;
		game->player.height = 0;
	}
	if (game->exit.ptr)
	{
		mlx_delete_image(mlx, (mlx_image_t *)game->exit.ptr);
		game->exit.ptr = NULL;
		game->exit.width = 0;
		game->exit.height = 0;
	}
	if (game->collectible.ptr)
	{
		mlx_delete_image(mlx, (mlx_image_t *)game->collectible.ptr);
		game->collectible.ptr = NULL;
		game->collectible.width = 0;
		game->collectible.height = 0;
	}
	mlx_terminate(mlx);
	game->mlx = NULL;
}

void	cleanup_graphics(t_game *game)
{
	mlx_t	*mlx;

	if (!game)
		return ;
	mlx = (mlx_t *)game->mlx;
	if (mlx)
	{
		cleanup_images_part1(game, mlx);
		cleanup_images_part2(game, mlx);
	}
}
