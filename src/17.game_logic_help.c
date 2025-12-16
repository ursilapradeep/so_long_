/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17.game_logic_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/15 19:28:39 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->map)
		return ;
	i = 0;
	while (i < game->map_h)
	{
		if (game->map[i])
		{
			free(game->map[i]);
			game->map[i] = NULL;
		}
		i++;
	}
	free(game->map);
	game->map = NULL;
	game->map_h = 0;
	game->map_w = 0;
}

void	cleanup_and_exit(t_game *game, int code, const char *msg)
{
	if (msg)
	{
		if (code == 0)
		{
			ft_putendl_fd((char *)msg, 1);
			fflush(stdout);
		}
		else
			ft_putendl_fd((char *)msg, 2);
	}
	free_map(game);
	cleanup_graphics(game);
	exit(code);
}

static int	handle_exit_tile(t_game *game, int nx, int ny)
{
	void	*tmp;

	if (game->map[game->player_y][game->player_x] != 'E')
		game->map[game->player_y][game->player_x] = '0';
	if (game->collected != game->collectible_count)
		return (0);
	game->moves++;
	printf("Moves: %d\n", game->moves);
	game->player_x = nx;
	game->player_y = ny;
	game->won = 1;
	game->win_time = mlx_get_time() * 1000;
	tmp = game->exit.ptr;
	game->exit.ptr = game->player_exit_unlocked.ptr;
	game->player_exit_unlocked.ptr = tmp;
	render_map(game);
	return (1);
}

int	handle_target_tile(t_game *game, int nx, int ny, char target)
{
	if (target == '1')
		return (0);
	if (target == 'E')
		return (handle_exit_tile(game, nx, ny));
	if (target == 'C')
	{
		game->collected++;
		game->map[ny][nx] = '0';
	}
	return (1);
}

int	apply_move(t_game *game, int nx, int ny)
{
	if (game->player_x >= 0 && game->player_y >= 0
		&& game->map[game->player_y][game->player_x] != 'E')
		game->map[game->player_y][game->player_x] = '0';
	if (game->map[ny][nx] != 'E')
		game->map[ny][nx] = 'P';
	game->player_x = nx;
	game->player_y = ny;
	game->moves++;
	printf("Moves: %d\n", game->moves);
	render_map(game);
	return (1);
}
