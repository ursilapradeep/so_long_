/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11.validate_tex_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:11:47 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 12:15:29 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_player_char(char ch, int x, int y, t_player_info *player)
{
	if (!player)
		return ;
	if (ch == 'P')
	{
		player->count++;
		player->start_x = x;
		player->start_y = y;
	}
}

void	scan_row_for_player(t_game *game, int y, t_player_info *player)
{
	int		x;
	char	ch;

	if (!game || !game->map || !player)
		return ;
	x = 0;
	while (game->map[y][x] != '\0' && game->map[y][x] != '\n')
	{
		ch = game->map[y][x];
		handle_player_char(ch, x, y, player);
		x++;
	}
}
