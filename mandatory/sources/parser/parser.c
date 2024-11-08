/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:07 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/11/01 15:26:37 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_line(char *line, int *player_nb, t_wall *wall)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW ", line[i]))
			free_print("invalid character in map\n", wall);
		if (ft_strchr("NSWE", line[i]))
			*player_nb += 1;
		i++;
	}
}

void	check_nb_of_players(int player_nb, t_wall *wall)
{
	if (player_nb == 0)
		free_print("there is no player on the map\n", wall);
	if (player_nb > 1)
		free_print("there is more then one player\n", wall);
}

char	**save_map(int fd, char *first_line, t_wall *wall)
{
	char	**map;
	char	*line;
	char	*tmp;
	int		player_nb;

	player_nb = 0;
	map = NULL;
	tmp = ft_strtrim(first_line, "\n");
	check_map_line(tmp, &player_nb, wall);
	map = ft_arradd_back(map, tmp);
	ft_alloc(0, tmp, FREE_PTR);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) == 1 && !strncmp(line, "\n", ft_strlen(line)))
			free_print("invalid map\n", wall);
		tmp = ft_strtrim(line, "\n");
		ft_alloc(0, line, FREE_PTR);
		check_map_line(tmp, &player_nb, wall);
		map = ft_arradd_back(map, tmp);
		ft_alloc(0, tmp, FREE_PTR);
	}
	return (check_nb_of_players(player_nb, wall), map);
}

void	read_file(int fd, t_game_env **game_env)
{
	char	*line;
	char	**temp_arr;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (check_empty_line(line) == 1)
			continue ;
		temp_arr = spliter(line);
		if ((*game_env)->ceiling_status == -1 || (*game_env)->floor_status == -1
			|| !(*game_env)->wall->east || !(*game_env)->wall->west
			|| !(*game_env)->wall->north || !(*game_env)->wall->south)
			save_tools(temp_arr, game_env);
		else
		{
			(*game_env)->map = save_map(fd, line, (*game_env)->wall);
			break ;
		}
		ft_alloc(0, temp_arr, FREE_PTR);
	}
	if (!(*game_env)->map)
		free_print("ivalid map\n", (*game_env)->wall);
}

t_game_env	*parser(int ac, char **av)
{
	t_game_env	*game_env;
	char		**arr;
	int			fd;

	fd = 0;
	arr = NULL;
	game_env = NULL;
	if (ac == 1)
		print_err(1, "messing parameter\n");
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 4))
		print_err(1, "invalid format. should be *.cub\n");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_err(3, "can't open file ", av[1], "\n");
	game_env = ft_alloc(sizeof(t_game_env), game_env, CALLOC);
	if (!game_env)
		print_err(1, "malloc failed\n");
	game_env->ceiling_status = -1;
	game_env->floor_status = -1;
	game_env->wall = ft_alloc(sizeof(t_wall), game_env->wall, CALLOC);
	read_file(fd, &game_env);
	check_map(game_env);
	return (game_env);
}
