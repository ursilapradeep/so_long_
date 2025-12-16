/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.initialize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:26:03 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:26:09 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	void	init_game_images(t_game *game)
{
	if (!game)
		return ;
	game->floor.ptr = NULL;
	game->floor.width = 0;
	game->floor.height = 0;
	game->wall.ptr = NULL;
	game->wall.width = 0;
	game->wall.height = 0;
	game->player.ptr = NULL;
	game->player.width = 0;
	game->player.height = 0;
	game->exit.ptr = NULL;
	game->exit.width = 0;
	game->exit.height = 0;
	game->collectible.ptr = NULL;
	game->collectible.width = 0;
	game->collectible.height = 0;
	game->mlx = NULL;
	game->window = NULL;
}

int	init_game_state(t_game *game)
{
	if (!game)
		return (1);
	memset(game, 0, sizeof * game);
	game->player_x = -1;
	game->player_y = -1;
	init_game_images (game);
	return (0);
}
