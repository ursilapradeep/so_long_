/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.validate_map_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:27:59 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:28:03 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	alloc_reach_resources(t_reach *ctx, int w, int h)
{
	ctx->w = w;
	ctx->h = h;
	ctx->visited = (int *)calloc((size_t)w * (size_t)h, sizeof(int));
	if (!ctx->visited)
		return (1);
	return (0);
}

void	ff_dfs(t_reach *ctx, int x, int y)
{
	int	idx;

	if (x < 0 || x >= ctx->w || y < 0 || y >= ctx->h)
		return ;
	idx = y * ctx->w + x;
	if (ctx->visited[idx] || ctx->map[y][x] == '1')
		return ;
	ctx->visited[idx] = 1;
	if (ctx->map[y][x] == 'C')
		ctx->rx_c++;
	else if (ctx->map[y][x] == 'E')
		ctx->exit_reached = 1;
	ff_dfs(ctx, x, y - 1);
	ff_dfs(ctx, x, y + 1);
	ff_dfs(ctx, x - 1, y);
	ff_dfs(ctx, x + 1, y);
}

int	check_row_width(t_game *g, int y)
{
	int	x;

	x = 0;
	while (g->map[y][x] != '\n' && g->map[y][x] != '\0')
		x++;
	return (x != g->map_w);
}

int	check_top_bottom_walls(t_game *g, int y)
{
	int	i;

	i = 0;
	while (i < g->map_w)
	{
		if (g->map[y][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_side_walls(t_game *g, int y)
{
	if (g->map[y][0] != '1' || g->map[y][g->map_w - 1] != '1')
		return (1);
	return (0);
}
