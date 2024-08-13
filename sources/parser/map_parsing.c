/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:34:36 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/13 15:54:59 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int *player_position(char **map)
{
	int j;
	int i;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				return ((int[2]){i, j});
			j++;
		}
		i++;
	}
	return ((int[2]){0, 0});
}

void flod_fill_checker(char **map, int *xy, t_wall *wall)
{
	if ((map[xy[0]][xy[1]] == '0' || map[xy[0]][xy[1]] == '\0') && (xy[0] <= 0 || xy[1] <= 0 || xy[0] >= (int)ft_arrsize(map) - 1 || xy[1] >= (int)ft_strlen(map[xy[0]]) - 1))
		free_print("invalid map. The map must be closed/surrounded by walls\n", wall);
	if (map[xy[0]][xy[1]] == ' ' || map[xy[0]][xy[1]] == '\0')
		free_print("invalid map. The map must be closed/surrounded by walls\n", wall);
	else if (map[xy[0]][xy[1]] == '0')
	{
		map[xy[0]][xy[1]] = '1';
		flod_fill_checker(map, (int[2]){xy[0] + 1, xy[1]}, wall);
		flod_fill_checker(map, (int[2]){xy[0] - 1, xy[1]}, wall);
		flod_fill_checker(map, (int[2]){xy[0], xy[1] + 1}, wall);
		flod_fill_checker(map, (int[2]){xy[0], xy[1] - 1}, wall);
	}
	else
		return ;
}
void check_map(char **map, t_wall *wall)
{
	char **temp_map;
	int *xy;

	temp_map = map;
	xy = player_position(temp_map);
	temp_map[xy[0]][xy[1]] = '0';
	flod_fill_checker(map, xy, wall);
}
