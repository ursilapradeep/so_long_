/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.validate_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:27:44 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:27:50 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_error_and_return(const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
		write(2, msg, strlen(msg));
	write(2, "\n", 1);
	return (1);
}

int	check_reachability(t_game *game, int sx, int sy, int total_c)
{
	t_reach	ctx;
	int		w;
	int		h;

	w = game->map_w;
	h = game->map_h;
	ctx.map = game->map;
	if (alloc_reach_resources(&ctx, w, h) != 0)
		return (1);
	ctx.rx_c = 0;
	ctx.exit_reached = 0;
	ff_dfs(&ctx, sx, sy);
	free(ctx.visited);
	if (ctx.rx_c != total_c)
		return (print_error_and_return("Not all collectibles are reachable"));
	if (!ctx.exit_reached)
		return (print_error_and_return("Exit is not reachable"));
	return (0);
}

int	check_map_walls_and_rect(t_game *g)
{
	int	y;

	y = 0;
	while (y < g->map_h)
	{
		if (check_row_width(g, y))
			return (1);
		if (y == 0 || y == g->map_h - 1)
		{
			if (check_top_bottom_walls(g, y))
				return (1);
		}
		else
		{
			if (check_side_walls(g, y))
				return (1);
		}
		y++;
	}
	return (0);
}

int	check_map_elements(t_game *game)
{
	int	p_count;
	int	e_count;
	int	c_count;
	int	start_x;
	int	start_y;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	start_x = -1;
	start_y = -1;
	if (scan_counts_validate(game, &e_count, &c_count) != 0)
		return (1);
	if (scan_player_count(game, &p_count, &start_x, &start_y) != 0)
		return (1);
	if (p_count != 1)
		return (print_error_and_return("Error"));
	if (e_count != 1)
		return (print_error_and_return("Error"));
	if (c_count < 1)
		return (print_error_and_return("Error"));
	if (check_reachability(game, start_x, start_y, c_count) != 0)
		return (1);
	return (0);
}

int	validate_map(t_game *game)
{
	if (check_map_walls_and_rect(game))
		return (1);
	if (check_map_elements(game))
		return (1);
	return (0);
}
