/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.game_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:41:00 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 16:09:36 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_invalid_map(void)
{
	const char	*msg;

	msg = "Error\nInvalid map\n";
	write(2, msg, strlen(msg));
	exit(1);
}

char	*prepare_get_map(t_game *game, char *map_path)
{
	const char	*err;

	if (!map_path)
	{
		err = "Error\n Incorrect Map\n";
		write(2, err, ft_strlen(err));
		return (NULL);
	}
	if (init_game_state(game) != 0)
	{
		free(map_path);
		return (NULL);
	}
	if (open_map_file(game, map_path) != 0
		|| parse_map_file(game) != 0
		|| validate_map(game) != 0)
	{
		err = "Error\nFailed to open/parse/validate map\n";
		write(2, err, ft_strlen(err));
		free(map_path);
		return (NULL);
	}
	return (map_path);
}

int	start_game(t_game *game, char *map_path)
{
	if (setup_game_graphics(game) != 0)
	{
		cleanup_graphics(game);
		free(map_path);
		return (1);
	}
	render_map(game);
	mlx_key_hook(game->mlx, handle_keypress, game);
	mlx_close_hook(game->mlx, close_game, game);
	mlx_loop_hook(game->mlx, win_update, game);
	mlx_loop(game->mlx);
	cleanup_graphics(game);
	free(map_path);
	return (0);
}
