/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:15:53 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/16 10:17:47 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define TILE_WIDTH 32
# define TILE_HEIGHT 32
# define MAX_MAP_WIDTH 2500
# define MAX_MAP_HEIGHT 2500
# include "libft.h"
# include <MLX42/MLX42.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <stdint.h>

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
}				t_img;

typedef struct s_game
{
	int			fd;
	void		*mlx;
	void		*window;
	char		**map;
	int			map_w;
	int			map_h;
	int			player_x;
	int			player_y;
	int			collectible_count;
	int			collected;
	int			exit_found;
	int			moves;
	int			won;
	uint64_t	win_time;
	t_img		floor;
	t_img		wall;
	t_img		player;
	t_img		exit;
	t_img		collectible;
	t_img		player_exit_unlocked;
}	t_game;

typedef struct s_reach
{
	int		w;
	int		h;
	int		*visited;
	char	**map;
	int		rx_c;
	int		exit_reached;
}	t_reach;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player_info
{
	int	count;
	int	start_x;
	int	start_y;
}	t_player_info;

size_t		ft_strlen(const char *s);
int			init_game_state(t_game *game);
char		*get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_substr(const char *s, unsigned int start, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		validate_args(int argc, char **argv);
char		*try_open_copy(const char *p);
char		*try_dir_for_map(const char *dir, const char *arg);
void		exit_invalid_map(void);
char		*prepare_get_map(t_game *game, char *map_path);
int			start_game(t_game *game, char *map_path);
int			open_map_file(t_game *game, char *map_path);
int			parse_map_file(t_game *game);
int			validate_map(t_game *game);
int			scan_counts_validate(t_game *game, int *e_count, int *c_count);
int			scan_player_count(t_game *game, int *p_count,
				int *start_x, int *start_y);
int			setup_game_graphics(t_game *game);
int			render_map(t_game *game);
void		draw_player_image(mlx_t *mlx, t_game *game,
				mlx_image_t *img, t_point pos);
mlx_image_t	*get_tile_image(t_game *game, char tile);
int			gfx_init_window(t_game *game);
int			load_png_to_img(mlx_t *mlx, const char *path, t_img *out);
int			gfx_load_textures_part1(t_game *game);
int			gfx_load_player(t_game *game);
int			gfx_load_collectible(t_game *game);
int			gfx_load_textures_part2(t_game *game);
int			gfx_load_exit_unlocked(t_game *game);
int			move_player(t_game *game, int dx, int dy);
void		handle_keypress(mlx_key_data_t keydata, void *param);
void		close_game(void *param);
int			handle_target_tile(t_game *game, int nx, int ny, char target);
int			apply_move(t_game *game, int nx, int ny);
void		cleanup_and_exit(t_game *game, int csode, const char *msg);
void		free_map(t_game *game);
void		cleanup_graphics(t_game *game);
void		win_update(void *param);
int			print_error_and_return(const char *msg);
void		ff_dfs(t_reach *ctx, int x, int y);
int			alloc_reach_resources(t_reach *ctx, int w, int h);
int			check_map_walls_and_rect(t_game *g);
int			check_map_elements(t_game *game);
int			check_reachability(t_game *game, int sx, int sy, int total_c);
int			check_row_width(t_game *g, int y);
int			check_top_bottom_walls(t_game *g, int y);
int			check_side_walls(t_game *g, int y);
int			validate_and_count_chars(char ch, int *e_count, int *c_count);
void		scan_row_for_player(t_game *game, int y, t_player_info *player);
void		cleanup_map_read(t_game *game, int fd, char *line, int line_index);

#endif