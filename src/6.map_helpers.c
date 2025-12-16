/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.map_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:27:16 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 19:27:20 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_map_read(t_game *game, int fd, char *line, int line_index)
{
	free(line);
	while (line_index-- > 0)
		free(game->map[line_index]);
	close(fd);
}
