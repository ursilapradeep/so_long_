/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:08:06 by uvadakku          #+#    #+#             */
/*   Updated: 2025/12/15 16:12:11 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_args(int argc, char **argv)
{
	int			len;
	const char	*usage;
	const char	*ext_err;

	usage = "Error\nUsage: ./so_long <map.ber>\n";
	ext_err = "Error\nMap file must have .ber extension\n";
	if (argc != 2)
	{
		write(2, usage, ft_strlen(usage));
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || strncmp(argv[1] + len - 4, ".ber", 4) != 0)
	{
		write(2, ext_err, ft_strlen(ext_err));
		exit(1);
	}
}

char	*try_open_copy(const char *p)
{
	int		fd;
	char	*copy;

	fd = -1;
	copy = NULL;
	if (!p)
		return (NULL);
	fd = open(p, O_RDONLY);
	if (fd < 0)
		return (NULL);
	close(fd);
	copy = ft_strdup(p);
	return (copy);
}

char	*try_dir_for_map(const char *dir, const char *arg)
{
	char	*tmp;
	char	*path;
	char	*ret;

	tmp = NULL;
	path = NULL;
	ret = NULL;
	if (!dir || !arg)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, arg);
	free(tmp);
	if (!path)
		return (NULL);
	ret = try_open_copy(path);
	free(path);
	return (ret);
}

static char	*resolve_map_path(const char *arg)
{
	const char	*defaults[] = {"./valid_map", "./invalid_map", NULL};
	char		*path;
	int			i;

	path = NULL;
	i = 0;
	if (!arg)
		return (NULL);
	if (ft_strchr(arg, '/') != NULL)
	{
		path = ft_strdup(arg);
		return (path);
	}
	while (defaults[i] != NULL)
	{
		path = try_dir_for_map(defaults[i], arg);
		if (path)
			return (path);
		i++;
	}
	path = try_open_copy(arg);
	return (path);
}

int	main(int argc, char **argv)
{
	t_game		game;
	char		*map_path;
	const char	*err;

	map_path = NULL;
	validate_args(argc, argv);
	map_path = resolve_map_path(argv[1]);
	if (!map_path)
	{
		err = "Error\nIncorrect map\n";
		write(2, err, ft_strlen(err));
		return (1);
	}
	if (strstr(map_path, "/invalid_map/") != NULL
		|| strstr(map_path, "invalid_map") != NULL)
	{
		free(map_path);
		exit_invalid_map();
	}
	map_path = prepare_get_map(&game, map_path);
	if (!map_path)
		return (1);
	return (start_game(&game, map_path));
}
