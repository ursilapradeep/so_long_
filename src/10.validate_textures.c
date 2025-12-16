/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.validate_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:03:47 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 12:18:27 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_walls(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	while (x < game->map_w)
	{
		if (game->map[0][x] != '1' || game->map[game->map_h - 1][x] != '1')
			return (print_error_and_return("Error"));
		x++;
	}
	y = 0;
	while (y < game->map_h)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_w - 1] != '1')
			return (print_error_and_return("Error"));
		y++;
	}
	return (0);
}

int	validate_and_count_chars(char ch, int *e_count, int *c_count)
{
	if (!e_count || !c_count)
		return (1);
	if (ch == 'E')
		(*e_count)++;
	else if (ch == 'C')
		(*c_count)++;
	else if (ch != '0' && ch != '1' && ch != 'P')
		return (print_error_and_return("Error\nInvalid character in map"));
	return (0);
}

int	scan_counts_validate(t_game *game, int *e_count, int *c_count)
{
	int		y;
	int		x;
	char	ch;

	if (check_walls(game))
		return (1);
	*e_count = 0;
	*c_count = 0;
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		ch = game->map[y][x];
		while (ch != '\0' && ch != '\n')
		{
			if (validate_and_count_chars(ch, e_count, c_count))
				return (1);
			x++;
			ch = game->map[y][x];
		}
		y++;
	}
	return (0);
}

int	scan_player_count(t_game *game, int *p_count, int *start_x, int *start_y)
{
	int				y;
	t_player_info	player;

	player.count = 0;
	player.start_x = -1;
	player.start_y = -1;
	y = 0;
	while (y < game->map_h)
	{
		scan_row_for_player(game, y, &player);
		y++;
	}
	*p_count = player.count;
	*start_x = player.start_x;
	*start_y = player.start_y;
	return (0);
}
