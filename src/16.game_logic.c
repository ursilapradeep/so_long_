/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16.game_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:21:22 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 15:53:19 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_player(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	char	target;

	if (!game || !game->map || game->won)
		return (0);
	nx = game->player_x + dx;
	ny = game->player_y + dy;
	if (ny < 0 || ny >= game->map_h || nx < 0 || nx >= game->map_w)
		return (0);
	target = game->map[ny][nx];
	if (!handle_target_tile(game, nx, ny, target))
		return (0);
	if (game->won)
		return (1);
	return (apply_move(game, nx, ny));
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g)
		return ;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_W)
		move_player(g, 0, -1);
	else if (keydata.key == MLX_KEY_S)
		move_player(g, 0, 1);
	else if (keydata.key == MLX_KEY_A)
		move_player(g, -1, 0);
	else if (keydata.key == MLX_KEY_D)
		move_player(g, 1, 0);
	else if (keydata.key == MLX_KEY_ESCAPE)
		cleanup_and_exit(g, 0, NULL);
}

void	close_game(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (g)
		cleanup_and_exit(g, 0, NULL);
}

void	win_update(void *param)
{
	t_game		*game;
	uint64_t	now;

	game = (t_game *)param;
	if (game->won)
	{
		now = mlx_get_time() * 1000;
		if (now - game->win_time >= 1500)
		{
			cleanup_and_exit(game, 0, "You win!");
		}
	}
}
